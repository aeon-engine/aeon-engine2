// Distributed under the BSD 2-Clause License - Copyright 2019-2021 Robin Degen

#include "dx11_context.h"
#include "dx11_rhi_sampler.h"
#include "dx11_rhi_texture.h"
#include "dx11_device.h"
#include "dx11_rhi_converters.h"
#include "dx11_rhi_shader.h"
#include "dx11_rhi_buffer.h"
#include "dx11_rhi_shader_resource_view.h"
#include "dx11_rhi_graphics_pipeline_state.h"
#include "checked_hresult.h"
#include <aeon/common/assert.h>

namespace aeon::engine::rhi::dx11
{

dx11_context::dx11_context(dx11_device &device, ID3D11DeviceContext *context) noexcept
    : device_{device}
    , context_{context}
{
}

dx11_context::~dx11_context() = default;

void dx11_context::set_vertex_buffer(vertex_buffer &buffer, const std::uint32_t stride, const std::uint32_t offset, const std::uint32_t slot)
{
    auto d3d_buffer = buffer.native_impl<dx11_rhi_vertex_buffer>()->buffer.Get();
    context_->IASetVertexBuffers(slot, 1, &d3d_buffer, &stride, &offset);
}

void dx11_context::set_index_buffer(index_buffer &buffer, const common::format format, const std::uint32_t offset)
{
    context_->IASetIndexBuffer(buffer.native_impl<dx11_rhi_index_buffer>()->buffer.Get(), convert_format(format), offset);
}

void dx11_context::set_shader_resource_view(graphics_shader &shader, const std::uint32_t index, shader_resource_view *view)
{
    aeon_assert_index_bounds(index, D3D11_COMMONSHADER_INPUT_RESOURCE_SLOT_COUNT);

    ID3D11ShaderResourceView *resource_view = nullptr;

    if (view)
        resource_view = view->native_impl<dx11_rhi_shader_resource_view>()->resource_view.Get();

    device_.internal_set_shader_resource_view(context_.Get(), shader.frequency(), index, resource_view);
}

void dx11_context::set_shader_constant_buffer(graphics_shader &shader, const std::uint32_t index, constant_buffer *buffer)
{
    aeon_assert_index_bounds(index, D3D11_COMMONSHADER_CONSTANT_BUFFER_API_SLOT_COUNT);

    ID3D11Buffer *d3dbuffer = nullptr;

    if (buffer)
        d3dbuffer = buffer->native_impl<dx11_rhi_constant_buffer>()->buffer.Get();

    device_.internal_set_shader_constant_buffer(context_.Get(), shader.frequency(), index, d3dbuffer);
}

void dx11_context::set_shader_sampler(graphics_shader &shader, const std::uint32_t index, sampler_state *sampler)
{
    ID3D11SamplerState *sampler_state = nullptr;

    if (sampler)
        sampler_state = sampler->native_impl<dx11_rhi_sampler_state>()->state.Get();

    switch (shader.frequency())
    {
        case shader_frequency::vertex:
            context_->VSSetSamplers(index, 1, &sampler_state);
            return;
        case shader_frequency::hull:
            context_->HSSetSamplers(index, 1, &sampler_state);
            return;
        case shader_frequency::domain:
            context_->DSSetSamplers(index, 1, &sampler_state);
            return;
        case shader_frequency::pixel:
            context_->PSSetSamplers(index, 1, &sampler_state);
            return;
        case shader_frequency::geometry:
            context_->GSSetSamplers(index, 1, &sampler_state);
            return;
        case shader_frequency::compute:
            context_->CSSetSamplers(index, 1, &sampler_state);
            return;
        default:
            std::abort();
    }
}

void *dx11_context::map(vertex_buffer &resource, const map_mode map_mode)
{
    return map(resource.native_impl<dx11_rhi_vertex_buffer>()->buffer.Get(), 0, map_mode);
}

void dx11_context::unmap(vertex_buffer &resource)
{
    context_->Unmap(resource.native_impl<dx11_rhi_vertex_buffer>()->buffer.Get(), 0);
}

void *dx11_context::map(index_buffer &resource, const map_mode map_mode)
{
    return map(resource.native_impl<dx11_rhi_index_buffer>()->buffer.Get(), 0, map_mode);
}

void dx11_context::unmap(index_buffer &resource)
{
    context_->Unmap(resource.native_impl<dx11_rhi_index_buffer>()->buffer.Get(), 0);
}

void *dx11_context::map(constant_buffer &resource, const map_mode map_mode)
{
    return map(resource.native_impl<dx11_rhi_constant_buffer>()->buffer.Get(), 0, map_mode);
}

void dx11_context::unmap(constant_buffer &resource)
{
    context_->Unmap(resource.native_impl<dx11_rhi_constant_buffer>()->buffer.Get(), 0);
}

void *dx11_context::map(texture2d &resource, const std::uint32_t sub_resource, const map_mode map_mode)
{
    return map(resource.native_impl<dx11_rhi_texture2d>()->texture.Get(), sub_resource, map_mode);
}

void dx11_context::unmap(texture2d &resource, const std::uint32_t sub_resource)
{
    context_->Unmap(resource.native_impl<dx11_rhi_texture2d>()->texture.Get(), static_cast<UINT>(sub_resource));
}

void dx11_context::set_viewport(const viewport &viewport)
{
    D3D11_VIEWPORT d3d_viewport{};
    d3d_viewport.Width = math::width(viewport.rectangle);
    d3d_viewport.Height = math::height(viewport.rectangle);
    d3d_viewport.MinDepth = viewport.depth.begin;
    d3d_viewport.MaxDepth = viewport.depth.end;

    const auto left_top = math::left_top(viewport.rectangle);
    d3d_viewport.TopLeftX = left_top.x;
    d3d_viewport.TopLeftY = left_top.y;

    context_->RSSetViewports(1, &d3d_viewport);
}

void dx11_context::set_graphics_pipeline_state(graphics_pipeline_state &state)
{
    const auto &dx11_state = state.native_impl<dx11_rhi_graphics_pipeline_state>();
    const auto bound_shader_state = dx11_state->bound_shader_state;
    const auto blend_state = dx11_state->blend_state;
    const auto rasterizer_state = dx11_state->rasterizer_state;
    const auto depth_stencil_state = dx11_state->depth_stencil_state;

    // TODO: Do we always need to unbind everything?
    // device_.internal_unbind_shader_resources();

    if (blend_state.get())
        context_->OMSetBlendState(blend_state->state.Get(), nullptr, 0xffffffff);
    else
        context_->OMSetBlendState(nullptr, nullptr, 0xffffffff);

    context_->RSSetState(rasterizer_state->state.Get());

    if (depth_stencil_state.get())
        context_->OMSetDepthStencilState(depth_stencil_state->state.Get(), 0);
    else
        context_->OMSetDepthStencilState(nullptr, 0);

    context_->IASetInputLayout(bound_shader_state->input_layout.Get());

    if (bound_shader_state->has_vertex_shader()) [[likely]]
        context_->VSSetShader(bound_shader_state->vertex_shader()->native_impl<dx11_rhi_vertex_shader>()->shader.Get(), nullptr, 0);
    else
        context_->VSSetShader(nullptr, nullptr, 0);

    if (bound_shader_state->has_pixel_shader()) [[likely]]
        context_->PSSetShader(bound_shader_state->pixel_shader()->native_impl<dx11_rhi_pixel_shader>()->shader.Get(), nullptr, 0);
    else
        context_->PSSetShader(nullptr, nullptr, 0);

    context_->IASetPrimitiveTopology(convert_primitive_topology(dx11_state->topology()));
}

void dx11_context::draw_indexed(const std::uint32_t index_count, const std::uint32_t index_offset, const std::int32_t base_vertex_offset)
{
    context_->DrawIndexed(index_count, index_offset, base_vertex_offset);
}

void *dx11_context::map(ID3D11Resource *resource, const std::uint32_t sub_resource, const map_mode map_mode) const
{
    D3D11_MAPPED_SUBRESOURCE mapped_resource{};
    checked_hresult{context_->Map(resource, static_cast<UINT>(sub_resource), convert_map_mode(map_mode), 0, &mapped_resource)};
    return mapped_resource.pData;
}

} // namespace aeon::engine::rhi::dx11

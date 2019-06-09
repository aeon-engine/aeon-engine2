// Distributed under the BSD 2-Clause License - Copyright 2019-2021 Robin Degen

#include "dx11_device.h"
#include "dx11_rhi_rasterizer_state.h"
#include "dx11_rhi_shader.h"
#include "dx11_rhi_texture.h"
#include "dx11_rhi_sampler.h"
#include "dx11_rhi_buffer.h"
#include "dx11_rhi_blend_state.h"
#include "dx11_rhi_depth_stencil_state.h"
#include "dx11_rhi_bound_shader_state.h"
#include "dx11_rhi_shader_resource_view.h"
#include "dx11_rhi_graphics_pipeline_state.h"
#include "dx11_rhi_converters.h"
#include "checked_hresult.h"
#include <aeon/platform/native_handles.h>
#include <vector>

namespace aeon::rhi::dx11
{

namespace internal
{

[[nodiscard]] auto create_buffer(ID3D11Device *device, const resource_data &initial_data, const usage usage, const D3D11_BIND_FLAG bind_flags, const common::flags<cpu_access> cpu_access_flags)
{
    D3D11_BUFFER_DESC buffer_description{};
    buffer_description.Usage = convert_usage(usage);
    buffer_description.ByteWidth = static_cast<UINT>(initial_data.size());
    buffer_description.BindFlags = bind_flags;
    buffer_description.CPUAccessFlags = static_cast<UINT>(cpu_access_flags);
    buffer_description.MiscFlags = 0;
    buffer_description.StructureByteStride = 0;

    D3D11_SUBRESOURCE_DATA subresource_data{};
    subresource_data.pSysMem = initial_data.data();
    subresource_data.SysMemPitch = 0;
    subresource_data.SysMemSlicePitch = 0;

    ID3D11Buffer *buffer;
    checked_hresult{device->CreateBuffer(&buffer_description, &subresource_data, &buffer)};
    return buffer;
}

} // namespace internal

dx11_device::dx11_device()
    : adapter_description_{}
    , feature_level_{D3D_FEATURE_LEVEL_11_0}
{
    ZeroMemory(bound_shader_resource_views_, std::size(bound_shader_resource_views_));
    ZeroMemory(bound_shader_resource_view_count_, std::size(bound_shader_resource_view_count_));
    ZeroMemory(bound_shader_constant_buffers_, std::size(bound_shader_constant_buffers_));
}

dx11_device::~dx11_device() = default;

void dx11_device::initialize([[maybe_unused]] platform::context &context, platform::window &window)
{
    Microsoft::WRL::ComPtr<IDXGIFactory> factory;
    checked_hresult{CreateDXGIFactory(__uuidof(IDXGIFactory), &factory)};

    Microsoft::WRL::ComPtr<IDXGIAdapter> adapter;
    checked_hresult{factory->EnumAdapters(0, &adapter)};

    Microsoft::WRL::ComPtr<IDXGIOutput> adapter_output;
    checked_hresult{adapter->EnumOutputs(0, &adapter_output)};

    const auto buffer_format = DXGI_FORMAT_R8G8B8A8_UNORM;

    UINT num_modes = 0;
    checked_hresult{adapter_output->GetDisplayModeList(buffer_format, DXGI_ENUM_MODES_INTERLACED, &num_modes, nullptr)};

    std::vector<DXGI_MODE_DESC> available_display_modes(num_modes);
    checked_hresult{adapter_output->GetDisplayModeList(buffer_format, DXGI_ENUM_MODES_INTERLACED, &num_modes, std::data(available_display_modes))};

    const auto window_dimensions = math::size2d<UINT>{window.dimensions()};
    UINT refresh_rate_numerator = 0;
    UINT refresh_rate_denominator = 0;

    for (const auto &display_mode : available_display_modes)
    {
        if ((display_mode.Width == window_dimensions.width) && (display_mode.Height == window_dimensions.height))
        {
            refresh_rate_numerator = display_mode.RefreshRate.Numerator;
            refresh_rate_denominator = display_mode.RefreshRate.Denominator;
        }
    }

    checked_hresult{adapter->GetDesc(&adapter_description_)};

    DXGI_SWAP_CHAIN_DESC swapchain_description{};
    swapchain_description.BufferCount = 1;
    swapchain_description.BufferDesc.Width = window_dimensions.width;
    swapchain_description.BufferDesc.Height = window_dimensions.height;
    swapchain_description.BufferDesc.Format = buffer_format;
    swapchain_description.Windowed = true;

    swapchain_description.BufferDesc.RefreshRate.Numerator = refresh_rate_numerator;     // 0
    swapchain_description.BufferDesc.RefreshRate.Denominator = refresh_rate_denominator; // 1

    swapchain_description.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;

    const auto native_handles = window.native_handles();
    swapchain_description.OutputWindow = native_handles.hwnd;

    // Multisampling
    swapchain_description.SampleDesc.Count = 1;
    swapchain_description.SampleDesc.Quality = 0;

    swapchain_description.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
    swapchain_description.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;

    swapchain_description.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;

    swapchain_description.Flags = 0;

    checked_hresult{D3D11CreateDeviceAndSwapChain(nullptr, D3D_DRIVER_TYPE_HARDWARE, nullptr, 0, &feature_level_, 1, D3D11_SDK_VERSION, &swapchain_description, &swap_chain_, &device_, nullptr,
                                                  &immediate_context_)};

    immediate_context_wrapper_ = std::make_unique<dx11_context>(*this, immediate_context_.Get());

    Microsoft::WRL::ComPtr<ID3D11Texture2D> back_buffer_texture;
    checked_hresult{swap_chain_->GetBuffer(0, __uuidof(ID3D11Texture2D), &back_buffer_texture)};
    checked_hresult{device_->CreateRenderTargetView(back_buffer_texture.Get(), nullptr, render_target_view_.GetAddressOf())};

    const auto depth_stencil_format = DXGI_FORMAT_D24_UNORM_S8_UINT;

    D3D11_TEXTURE2D_DESC depth_buffer_description{};
    depth_buffer_description.Width = window_dimensions.width;
    depth_buffer_description.Height = window_dimensions.height;
    depth_buffer_description.MipLevels = 1;
    depth_buffer_description.ArraySize = 1;
    depth_buffer_description.Format = depth_stencil_format;
    depth_buffer_description.SampleDesc.Count = 1;
    depth_buffer_description.SampleDesc.Quality = 0;
    depth_buffer_description.Usage = D3D11_USAGE_DEFAULT;
    depth_buffer_description.BindFlags = D3D11_BIND_DEPTH_STENCIL;
    depth_buffer_description.CPUAccessFlags = 0;
    depth_buffer_description.MiscFlags = 0;

    checked_hresult{device_->CreateTexture2D(&depth_buffer_description, nullptr, depth_stencil_buffer_.GetAddressOf())};

    D3D11_DEPTH_STENCIL_DESC depth_stencil_description{};
    depth_stencil_description.DepthEnable = true;
    depth_stencil_description.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
    depth_stencil_description.DepthFunc = D3D11_COMPARISON_LESS; // Might need to be D3D11_COMPARISON_LESS_EQUAL if we want to use a depth pre-pass?
    depth_stencil_description.StencilEnable = true;
    depth_stencil_description.StencilReadMask = 0xFF;
    depth_stencil_description.StencilWriteMask = 0xFF;
    depth_stencil_description.FrontFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
    depth_stencil_description.FrontFace.StencilDepthFailOp = D3D11_STENCIL_OP_INCR;
    depth_stencil_description.FrontFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
    depth_stencil_description.FrontFace.StencilFunc = D3D11_COMPARISON_ALWAYS;
    depth_stencil_description.BackFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
    depth_stencil_description.BackFace.StencilDepthFailOp = D3D11_STENCIL_OP_DECR;
    depth_stencil_description.BackFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
    depth_stencil_description.BackFace.StencilFunc = D3D11_COMPARISON_ALWAYS;

    checked_hresult{device_->CreateDepthStencilState(&depth_stencil_description, depth_stencil_state_.GetAddressOf())};
    immediate_context_->OMSetDepthStencilState(depth_stencil_state_.Get(), 1);

    D3D11_DEPTH_STENCIL_VIEW_DESC depth_stencil_view_description{};
    depth_stencil_view_description.Format = depth_stencil_format;
    depth_stencil_view_description.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
    depth_stencil_view_description.Texture2D.MipSlice = 0;

    checked_hresult{device_->CreateDepthStencilView(depth_stencil_buffer_.Get(), &depth_stencil_view_description, &depth_stencil_view_)};
    immediate_context_->OMSetRenderTargets(1, render_target_view_.GetAddressOf(), depth_stencil_view_.Get());
}

void dx11_device::shutdown()
{
    checked_hresult{swap_chain_->SetFullscreenState(false, nullptr)};
}

void dx11_device::clear_back_buffer(const common::color_rgba_f &clear_color)
{
    immediate_context_->ClearRenderTargetView(render_target_view_.Get(), common::ptr(clear_color));
}

void dx11_device::clear_depth_stencil_buffer(const float depth, const int stencil)
{
    immediate_context_->ClearDepthStencilView(depth_stencil_view_.Get(), D3D11_CLEAR_DEPTH, depth, static_cast<UINT8>(stencil));
}

void dx11_device::present(const int sync_interval)
{
    // TODO: Swap chain creation should probably be not be implicit..
    checked_hresult{swap_chain_->Present(static_cast<UINT>(sync_interval), 0)};
}

auto dx11_device::create_blend_state(const blend_state_initializer &initializer) -> blend_state_ref
{
    D3D11_BLEND_DESC blend_description{};
    blend_description.AlphaToCoverageEnable = initializer.enable_alpha_to_coverage;
    blend_description.IndependentBlendEnable = initializer.enable_independent_blend;
    blend_description.RenderTarget[0].BlendEnable = initializer.enable_blend;
    blend_description.RenderTarget[0].SrcBlend = convert_blend_factor(initializer.source_blend);
    blend_description.RenderTarget[0].DestBlend = convert_blend_factor(initializer.destination_blend);
    blend_description.RenderTarget[0].BlendOp = convert_blend_operation(initializer.operation);
    blend_description.RenderTarget[0].SrcBlendAlpha = convert_blend_factor(initializer.source_alpha_blend);
    blend_description.RenderTarget[0].DestBlendAlpha = convert_blend_factor(initializer.destination_alpha_blend);
    blend_description.RenderTarget[0].BlendOpAlpha = convert_blend_operation(initializer.alpha_operation);
    blend_description.RenderTarget[0].RenderTargetWriteMask = 0;

    ID3D11BlendState *blend_state;
    checked_hresult{device_->CreateBlendState(&blend_description, &blend_state)};
    return common::make_intrusive_ptr<dx11_rhi_blend_state>(blend_state);
}

auto dx11_device::create_rasterizer_state(const rasterizer_state_initializer &initializer) -> rasterizer_state_ref
{
    D3D11_RASTERIZER_DESC raster_description{};
    raster_description.FillMode = convert_fill_mode(initializer.fill_mode);
    raster_description.CullMode = convert_cull_mode(initializer.cull_mode);
    raster_description.FrontCounterClockwise = (initializer.winding_order == winding_order::counter_clockwise);
    raster_description.DepthBias = initializer.depth_bias;
    raster_description.DepthBiasClamp = initializer.depth_bias_clamp;
    raster_description.SlopeScaledDepthBias = initializer.slope_scaled_depth_bias;
    raster_description.DepthClipEnable = initializer.depth_clip_enable;
    raster_description.ScissorEnable = initializer.scissor_enable;
    raster_description.MultisampleEnable = initializer.multisample_enable;
    raster_description.AntialiasedLineEnable = initializer.antialiased_line_enable;

    ID3D11RasterizerState *d3d11_state;
    checked_hresult{device_->CreateRasterizerState(&raster_description, &d3d11_state)};
    return common::make_intrusive_ptr<dx11_rhi_rasterizer_state>(d3d11_state);
}

auto dx11_device::create_depth_stencil_state(const depth_stencil_state_initializer &initializer) -> depth_stencil_state_ref
{
    D3D11_DEPTH_STENCIL_DESC description{};
    description.DepthEnable = initializer.depth_enable;
    description.DepthWriteMask = convert_depth_write_mask(initializer.depth_write_mask);
    description.DepthFunc = convert_comparison_function(initializer.depth_function);
    description.StencilEnable = initializer.stencil_enable;
    description.StencilReadMask = initializer.stencil_read_mask;
    description.StencilWriteMask = initializer.stencil_write_mask;

    description.FrontFace.StencilFailOp = convert_stencil_op(initializer.front_face.fail_operation);
    description.FrontFace.StencilDepthFailOp = convert_stencil_op(initializer.front_face.depth_fail_operation);
    description.FrontFace.StencilPassOp = convert_stencil_op(initializer.front_face.pass_operation);
    description.FrontFace.StencilFunc = convert_comparison_function(initializer.front_face.function);

    description.BackFace.StencilFailOp = convert_stencil_op(initializer.back_face.fail_operation);
    description.BackFace.StencilDepthFailOp = convert_stencil_op(initializer.back_face.depth_fail_operation);
    description.BackFace.StencilPassOp = convert_stencil_op(initializer.back_face.pass_operation);
    description.BackFace.StencilFunc = convert_comparison_function(initializer.back_face.function);

    ID3D11DepthStencilState *state;
    checked_hresult{device_->CreateDepthStencilState(&description, &state)};
    return common::make_intrusive_ptr<dx11_rhi_depth_stencil_state>(state);
}

auto dx11_device::create_vertex_shader(const std::span<const std::byte> &data) -> vertex_shader_ref
{
    ID3D11VertexShader *shader;
    checked_hresult{device_->CreateVertexShader(std::data(data), std::size(data), nullptr, &shader)};
    return common::make_intrusive_ptr<dx11_rhi_vertex_shader>(shader, data);
}

auto dx11_device::create_pixel_shader(const std::span<const std::byte> &data) -> pixel_shader_ref
{
    ID3D11PixelShader *shader;
    checked_hresult{device_->CreatePixelShader(std::data(data), std::size(data), nullptr, &shader)};
    return common::make_intrusive_ptr<dx11_rhi_pixel_shader>(shader, data);
}

auto dx11_device::create_vertex_buffer(const resource_data initial_data, const usage usage, const common::flags<cpu_access> cpu_access_flags) -> vertex_buffer_ref
{
    auto buffer = internal::create_buffer(device_.Get(), initial_data, usage, D3D11_BIND_VERTEX_BUFFER, cpu_access_flags);
    return common::make_intrusive_ptr<dx11_rhi_vertex_buffer>(buffer, initial_data.size(), usage);
}

auto dx11_device::create_index_buffer(const resource_data initial_data, const usage usage, const common::flags<cpu_access> cpu_access_flags) -> index_buffer_ref
{
    auto buffer = internal::create_buffer(device_.Get(), initial_data, usage, D3D11_BIND_INDEX_BUFFER, cpu_access_flags);
    return common::make_intrusive_ptr<dx11_rhi_index_buffer>(buffer, initial_data.size(), usage);
}

auto dx11_device::create_constant_buffer(const resource_data initial_data, const usage usage, const common::flags<cpu_access> cpu_access_flags) -> constant_buffer_ref
{
    auto buffer = internal::create_buffer(device_.Get(), initial_data, usage, D3D11_BIND_CONSTANT_BUFFER, cpu_access_flags);
    return common::make_intrusive_ptr<dx11_rhi_constant_buffer>(buffer, initial_data.size(), usage);
}

auto dx11_device::create_texture2d(const math::size2d<imaging::image_view::dimensions_type> size, const std::uint32_t mip_levels, const format format, const texture_resource_data initial_data)
    -> texture2d_ref
{
    D3D11_SUBRESOURCE_DATA subresource_data{};
    subresource_data.pSysMem = initial_data.data();
    subresource_data.SysMemPitch = static_cast<UINT>(initial_data.stride_y());
    subresource_data.SysMemSlicePitch = static_cast<UINT>(initial_data.size());

    D3D11_TEXTURE2D_DESC description{};
    description.Width = static_cast<UINT>(size.width);
    description.Height = static_cast<UINT>(size.height);
    description.MipLevels = mip_levels;
    description.ArraySize = 1;
    description.SampleDesc.Count = 1;
    description.SampleDesc.Quality = 0;
    description.Usage = D3D11_USAGE_DEFAULT;
    description.Format = convert_format(format);
    description.BindFlags = D3D11_BIND_SHADER_RESOURCE;
    description.CPUAccessFlags = 0;
    description.MiscFlags = 0;

    Microsoft::WRL::ComPtr<ID3D11Texture2D> texture;
    checked_hresult{device_->CreateTexture2D(&description, &subresource_data, &texture)};
    return common::make_intrusive_ptr<dx11_rhi_texture2d>(texture.Get(), size, mip_levels, format);
}

auto dx11_device::create_shader_resource_view(texture &texture) -> shader_resource_view_ref
{
    D3D11_SHADER_RESOURCE_VIEW_DESC shader_resource_view_description{};
    shader_resource_view_description.Format = convert_format(texture.format());

    ID3D11Resource *resource = nullptr;
    if (texture.get_texture1d())
    {
        shader_resource_view_description.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE1D;
        // TODO
    }
    else if (texture.get_texture2d())
    {
        shader_resource_view_description.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
        resource = texture.native_impl<dx11_rhi_texture2d>()->texture.Get();
    }
    else if (texture.get_texture3d())
    {
        shader_resource_view_description.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE3D;
        // TODO
    }

    assert(resource);

    shader_resource_view_description.Texture2D.MostDetailedMip = 0;
    shader_resource_view_description.Texture2D.MipLevels = static_cast<UINT>(texture.mip_levels());

    ID3D11ShaderResourceView *view;
    checked_hresult{device_->CreateShaderResourceView(resource, &shader_resource_view_description, &view)};
    return common::make_intrusive_ptr<dx11_rhi_shader_resource_view>(view);
}

auto dx11_device::create_sampler_state(const sampler_state_settings &settings) -> sampler_state_ref
{
    D3D11_SAMPLER_DESC sampler_description{};
    sampler_description.Filter = convert_filter_type(settings.filter());
    sampler_description.AddressU = convert_wrap_mode(settings.wrap_mode_u());
    sampler_description.AddressV = convert_wrap_mode(settings.wrap_mode_v());
    sampler_description.AddressW = convert_wrap_mode(settings.wrap_mode_w());
    sampler_description.MipLODBias = settings.mip_lod_bias();
    sampler_description.MaxAnisotropy = settings.max_anisotropy();
    sampler_description.ComparisonFunc = D3D11_COMPARISON_ALWAYS;
    sampler_description.BorderColor[0] = 0;
    sampler_description.BorderColor[1] = 0;
    sampler_description.BorderColor[2] = 0;
    sampler_description.BorderColor[3] = 0;
    sampler_description.MinLOD = settings.min_lod();
    sampler_description.MaxLOD = settings.max_lod();

    ID3D11SamplerState *state;
    checked_hresult{device_->CreateSamplerState(&sampler_description, &state)};
    return common::make_intrusive_ptr<dx11_rhi_sampler_state>(settings, state);
}

auto dx11_device::create_bound_shader_state(const std::vector<input_layout_description> &input_layout, vertex_shader *vs, pixel_shader *ps) -> bound_shader_state_ref
{
    std::vector<D3D11_INPUT_ELEMENT_DESC> layout(std::size(input_layout));

    for (auto i = 0u; i < std::size(input_layout); ++i)
    {
        layout[i].SemanticName = input_layout[i].name.c_str();
        layout[i].SemanticIndex = 0;
        layout[i].Format = convert_format(input_layout[i].format);
        layout[i].InputSlot = 0;
        layout[i].AlignedByteOffset = input_layout[i].stride;
        layout[i].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
        layout[i].InstanceDataStepRate = 0;
    }

    // TODO: How to handle a nullptr vertex shader? Enforce input layout is empty? Additional overload?
    auto dx11_vertex_shader = vs->native_impl<dx11_rhi_vertex_shader>();

    ID3D11InputLayout *dx11_input_layout;
    checked_hresult{device_->CreateInputLayout(std::data(layout), static_cast<UINT>(std::size(layout)), std::data(dx11_vertex_shader->compiled_shader), std::size(dx11_vertex_shader->compiled_shader),
                                               &dx11_input_layout)};

    return common::make_intrusive_ptr<dx11_rhi_bound_shader_state>(dx11_input_layout, vs, ps);
}

auto dx11_device::create_graphics_pipeline_state(const graphics_pipeline_state_initializer &initializer) -> graphics_pipeline_state_ref
{
    dx11_rhi_blend_state *blend_state = nullptr;

    if (initializer.blend_state)
        blend_state = initializer.blend_state->native_impl<dx11_rhi_blend_state>();

    dx11_rhi_depth_stencil_state *depth_stencil_state = nullptr;

    if (initializer.depth_stencil_state)
        depth_stencil_state = initializer.depth_stencil_state->native_impl<dx11_rhi_depth_stencil_state>();

    return common::make_intrusive_ptr<dx11_rhi_graphics_pipeline_state>(initializer.bound_shader_state->native_impl<dx11_rhi_bound_shader_state>(), blend_state,
                                                                        initializer.rasterizer_state->native_impl<dx11_rhi_rasterizer_state>(), depth_stencil_state, initializer.topology);
}

auto dx11_device::get_immediate_context() const noexcept -> context &
{
    return *immediate_context_wrapper_;
}

auto dx11_device::get_dedicated_gpu_memory() const noexcept -> std::uint64_t
{
    return adapter_description_.DedicatedVideoMemory;
}

void dx11_device::internal_set_shader_resource_view(ID3D11DeviceContext *context, const shader_frequency frequency, const std::uint32_t index, ID3D11ShaderResourceView *view)
{
    bound_shader_resource_views_[static_cast<int>(frequency)][index] = view;

    if (auto &index_count = bound_shader_resource_view_count_[static_cast<int>(frequency)]; view != nullptr)
    {
        index_count = std::max(index_count, index);
    }
    else
    {
        if (index_count == index)
        {
            do
            {
                --index_count;
            } while (index_count > 0 && bound_shader_resource_views_[static_cast<int>(frequency)][index_count] == nullptr);
        }
    }

    switch (frequency)
    {
        case shader_frequency::vertex:
        {
            context->VSSetShaderResources(index, 1, &view);
            break;
        }
        case shader_frequency::hull:
        {
            context->HSSetShaderResources(index, 1, &view);
            break;
        }
        case shader_frequency::domain:
        {
            context->DSSetShaderResources(index, 1, &view);
            break;
        }
        case shader_frequency::pixel:
        {
            context->PSSetShaderResources(index, 1, &view);
            break;
        }
        case shader_frequency::geometry:
        {
            context->GSSetShaderResources(index, 1, &view);
            break;
        }
        case shader_frequency::compute:
        {
            context->CSSetShaderResources(index, 1, &view);
            break;
        }
        default:
            aeon_assert_fail("Shader frequency not implemented.");
    }
}

void dx11_device::internal_set_shader_constant_buffer(ID3D11DeviceContext *context, const shader_frequency frequency, const std::uint32_t index, ID3D11Buffer *buffer)
{
    bound_shader_constant_buffers_[static_cast<int>(frequency)][index] = buffer;

    switch (frequency)
    {
        case shader_frequency::vertex:
        {
            context->VSSetConstantBuffers(index, 1, &buffer);
            break;
        }
        case shader_frequency::hull:
        {
            context->HSSetConstantBuffers(index, 1, &buffer);
            break;
        }
        case shader_frequency::domain:
        {
            context->DSSetConstantBuffers(index, 1, &buffer);
            break;
        }
        case shader_frequency::pixel:
        {
            context->PSSetConstantBuffers(index, 1, &buffer);
            break;
        }
        case shader_frequency::geometry:
        {
            context->GSSetConstantBuffers(index, 1, &buffer);
            break;
        }
        case shader_frequency::compute:
        {
            context->CSSetConstantBuffers(index, 1, &buffer);
            break;
        }
        default:
            aeon_assert_fail("Shader frequency not implemented.");
    }
}

void dx11_device::internal_unbind_shader_resources()
{
    internal_unbind_shader_resource_views();
    internal_unbind_shader_constant_buffers();
}

void dx11_device::internal_unbind_shader_resource_views()
{
    internal_unbind_shader_resource_views(shader_frequency::vertex);
    internal_unbind_shader_resource_views(shader_frequency::hull);
    internal_unbind_shader_resource_views(shader_frequency::domain);
    internal_unbind_shader_resource_views(shader_frequency::pixel);
    internal_unbind_shader_resource_views(shader_frequency::geometry);
    internal_unbind_shader_resource_views(shader_frequency::compute);
}

void dx11_device::internal_unbind_shader_resource_views(const shader_frequency frequency)
{
    auto &index_count = bound_shader_resource_view_count_[static_cast<int>(frequency)];
    for (auto slot = 0u; slot < index_count; ++slot)
    {
        if (auto &view = bound_shader_resource_views_[static_cast<int>(frequency)][slot]; view != nullptr)
        {
            internal_set_shader_resource_view(immediate_context_.Get(), frequency, slot, nullptr);
            view = nullptr;
        }
    }

    index_count = 0;
}

void dx11_device::internal_unbind_shader_constant_buffers()
{
    internal_unbind_shader_constant_buffers(shader_frequency::vertex);
    internal_unbind_shader_constant_buffers(shader_frequency::hull);
    internal_unbind_shader_constant_buffers(shader_frequency::domain);
    internal_unbind_shader_constant_buffers(shader_frequency::pixel);
    internal_unbind_shader_constant_buffers(shader_frequency::geometry);
    internal_unbind_shader_constant_buffers(shader_frequency::compute);
}

void dx11_device::internal_unbind_shader_constant_buffers(const shader_frequency frequency)
{
    for (auto slot = 0; slot < D3D11_COMMONSHADER_CONSTANT_BUFFER_API_SLOT_COUNT; ++slot)
    {
        if (auto &view = bound_shader_constant_buffers_[static_cast<int>(frequency)][slot]; view != nullptr)
        {
            internal_set_shader_constant_buffer(immediate_context_.Get(), frequency, slot, nullptr);
            view = nullptr;
        }
    }
}

} // namespace aeon::rhi::dx11

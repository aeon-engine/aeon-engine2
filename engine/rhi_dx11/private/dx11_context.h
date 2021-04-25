// Distributed under the BSD 2-Clause License - Copyright 2019-2021 Robin Degen

#pragma once

#include <aeon/engine/rhi/context.h>
#include <d3d11.h>
#include <wrl/client.h>

namespace aeon::engine::rhi::dx11
{

class dx11_device;

class dx11_context final : public context
{
public:
    explicit dx11_context(dx11_device &device, ID3D11DeviceContext *context) noexcept;
    ~dx11_context() final;

    dx11_context(const dx11_context &) = delete;
    auto operator=(const dx11_context &) -> dx11_context & = delete;

    dx11_context(dx11_context &&) noexcept = delete;
    auto operator=(dx11_context &&) noexcept -> dx11_context & = delete;

    void set_vertex_buffer(vertex_buffer &buffer, const std::uint32_t stride, const std::uint32_t offset, const std::uint32_t slot) final;
    void set_index_buffer(index_buffer &buffer, const common::format format, const std::uint32_t offset) final;

    void set_shader_resource_view(graphics_shader &shader, const std::uint32_t index, shader_resource_view *view) final;
    void set_shader_constant_buffer(graphics_shader &shader, const std::uint32_t index, constant_buffer *buffer) final;
    void set_shader_sampler(graphics_shader &shader, const std::uint32_t index, sampler_state *sampler) final;

    [[nodiscard]] void *map(vertex_buffer &resource, const map_mode map_mode = map_mode::write_discard) final;
    void unmap(vertex_buffer &resource) final;

    [[nodiscard]] void *map(index_buffer &resource, const map_mode map_mode = map_mode::write_discard) final;
    void unmap(index_buffer &resource) final;

    [[nodiscard]] void *map(constant_buffer &resource, const map_mode map_mode = map_mode::write_discard) final;
    void unmap(constant_buffer &resource) final;

    [[nodiscard]] void *map(texture2d &resource, const std::uint32_t sub_resource = 0, const map_mode map_mode = map_mode::write_discard) final;
    void unmap(texture2d &resource, const std::uint32_t sub_resource = 0) final;

    void set_viewport(const viewport &viewport) final;

    void set_graphics_pipeline_state(graphics_pipeline_state &state) final;

    void draw_indexed(const std::uint32_t index_count, const std::uint32_t index_offset, const std::int32_t base_vertex_offset) final;

private:
    [[nodiscard]] void *map(ID3D11Resource *resource, const std::uint32_t sub_resource, const map_mode map_mode) const;

    dx11_device &device_;
    Microsoft::WRL::ComPtr<ID3D11DeviceContext> context_;
};

} // namespace aeon::engine::rhi::dx11

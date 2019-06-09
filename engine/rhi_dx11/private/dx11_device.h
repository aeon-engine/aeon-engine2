// Distributed under the BSD 2-Clause License - Copyright 2019-2021 Robin Degen

#pragma once

#include <aeon/rhi/device.h>
#include "dx11_context.h"
#include <wrl/client.h>
#include <d3dcommon.h>
#include <d3d11.h>
#include <dxgi.h>

namespace aeon::rhi::dx11
{

class dx11_device final : public device
{
public:
    dx11_device();
    ~dx11_device() final;

    dx11_device(const dx11_device &) = delete;
    auto operator=(const dx11_device &) -> dx11_device & = delete;

    dx11_device(dx11_device &&) noexcept = delete;
    auto operator=(dx11_device &&) noexcept -> dx11_device & = delete;

    void initialize(platform::context &context, platform::window &window) final;
    void shutdown() final;

    void clear_back_buffer(const common::color_rgba_f &clear_color) final;
    void clear_depth_stencil_buffer(const float depth, const int stencil) final;

    void present(const int sync_interval) final;

    [[nodiscard]] auto create_blend_state(const blend_state_initializer &initializer) -> blend_state_ref final;

    [[nodiscard]] auto create_rasterizer_state(const rasterizer_state_initializer &initializer) -> rasterizer_state_ref final;

    [[nodiscard]] auto create_depth_stencil_state(const depth_stencil_state_initializer &initializer) -> depth_stencil_state_ref final;

    [[nodiscard]] auto create_vertex_shader(const std::span<const std::byte> &data) -> vertex_shader_ref final;
    [[nodiscard]] auto create_pixel_shader(const std::span<const std::byte> &data) -> pixel_shader_ref final;

    [[nodiscard]] auto create_vertex_buffer(const resource_data initial_data, const usage usage, const common::flags<cpu_access> cpu_access_flags) -> vertex_buffer_ref final;
    [[nodiscard]] auto create_index_buffer(const resource_data initial_data, const usage usage, const common::flags<cpu_access> cpu_access_flags) -> index_buffer_ref final;
    [[nodiscard]] auto create_constant_buffer(const resource_data initial_data, const usage usage, const common::flags<cpu_access> cpu_access_flags) -> constant_buffer_ref final;

    [[nodiscard]] auto create_texture2d(const math::size2d<imaging::image_view::dimensions_type> size, const std::uint32_t mip_levels, const format format, const texture_resource_data initial_data)
        -> texture2d_ref final;

    [[nodiscard]] auto create_shader_resource_view(texture &texture) -> shader_resource_view_ref final;

    [[nodiscard]] auto create_sampler_state(const sampler_state_settings &settings) -> sampler_state_ref final;

    [[nodiscard]] auto create_bound_shader_state(const std::vector<input_layout_description> &input_layout, vertex_shader *vs, pixel_shader *ps) -> bound_shader_state_ref final;

    [[nodiscard]] auto create_graphics_pipeline_state(const graphics_pipeline_state_initializer &initializer) -> graphics_pipeline_state_ref final;

    [[nodiscard]] auto get_immediate_context() const noexcept -> context & final;

    [[nodiscard]] auto get_dedicated_gpu_memory() const noexcept -> std::uint64_t final;

    void internal_set_shader_resource_view(ID3D11DeviceContext *context, const shader_frequency frequency, const std::uint32_t index, ID3D11ShaderResourceView *view);
    void internal_set_shader_constant_buffer(ID3D11DeviceContext *context, const shader_frequency frequency, const std::uint32_t index, ID3D11Buffer *buffer);

    void internal_unbind_shader_resources();

    void internal_unbind_shader_resource_views();
    void internal_unbind_shader_resource_views(const shader_frequency frequency);

    void internal_unbind_shader_constant_buffers();
    void internal_unbind_shader_constant_buffers(const shader_frequency frequency);

private:
    DXGI_ADAPTER_DESC adapter_description_;
    D3D_FEATURE_LEVEL feature_level_;
    Microsoft::WRL::ComPtr<IDXGISwapChain> swap_chain_;
    Microsoft::WRL::ComPtr<ID3D11Device> device_;
    Microsoft::WRL::ComPtr<ID3D11DeviceContext> immediate_context_;
    std::unique_ptr<dx11_context> immediate_context_wrapper_;

    Microsoft::WRL::ComPtr<ID3D11RenderTargetView> render_target_view_;

    Microsoft::WRL::ComPtr<ID3D11Texture2D> depth_stencil_buffer_;
    Microsoft::WRL::ComPtr<ID3D11DepthStencilState> depth_stencil_state_;
    Microsoft::WRL::ComPtr<ID3D11DepthStencilView> depth_stencil_view_;

    ID3D11ShaderResourceView *bound_shader_resource_views_[total_shader_frequencies][D3D11_COMMONSHADER_INPUT_RESOURCE_SLOT_COUNT];
    std::uint32_t bound_shader_resource_view_count_[total_shader_frequencies];
    ID3D11Buffer *bound_shader_constant_buffers_[total_shader_frequencies][D3D11_COMMONSHADER_CONSTANT_BUFFER_API_SLOT_COUNT];
};

} // namespace aeon::rhi::dx11

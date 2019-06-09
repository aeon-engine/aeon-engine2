// Distributed under the BSD 2-Clause License - Copyright 2019-2021 Robin Degen

#pragma once

#include <aeon/rhi/shader.h>
#include <aeon/rhi/texture.h>
#include <aeon/rhi/format.h>
#include <aeon/rhi/buffer.h>
#include <aeon/rhi/resource_data.h>
#include <aeon/rhi/sampler_state.h>
#include <aeon/rhi/input_layout_description.h>
#include <aeon/rhi/rasterizer_state.h>
#include <aeon/rhi/shader_resource_view.h>
#include <aeon/rhi/graphics_pipeline_state.h>
#include <aeon/rhi/bound_shader_state.h>
#include <aeon/rhi/context.h>
#include <aeon/rhi/blend_state.h>
#include <aeon/rhi/depth_stencil_state.h>
#include <aeon/platform/window.h>
#include <aeon/imaging/image_view.h>
#include <aeon/math/size2d.h>
#include <aeon/common/color.h>
#include <span>

namespace aeon::rhi
{

class device
{
public:
    virtual ~device() = default;

    device(const device &) = delete;
    auto operator=(const device &) -> device & = delete;

    device(device &&) noexcept = delete;
    auto operator=(device &&) noexcept -> device & = delete;

    virtual void initialize(platform::context &context, platform::window &window) = 0;
    virtual void shutdown() = 0;

    virtual void clear_back_buffer(const common::color_rgba_f &clear_color = common::color_rgba_f{0.0f, 0.0f, 0.0f, 1.0f}) = 0;
    virtual void clear_depth_stencil_buffer(const float depth = 1.0f, const int stencil = 0) = 0;

    virtual void present(const int sync_interval = 1) = 0;

    [[nodiscard]] virtual auto create_blend_state(const blend_state_initializer &initializer) -> blend_state_ref = 0;

    [[nodiscard]] virtual auto create_rasterizer_state(const rasterizer_state_initializer &initializer) -> rasterizer_state_ref = 0;

    [[nodiscard]] virtual auto create_depth_stencil_state(const depth_stencil_state_initializer &initializer) -> depth_stencil_state_ref = 0;

    [[nodiscard]] virtual auto create_vertex_shader(const std::span<const std::byte> &data) -> vertex_shader_ref = 0;
    [[nodiscard]] virtual auto create_pixel_shader(const std::span<const std::byte> &data) -> pixel_shader_ref = 0;

    [[nodiscard]] virtual auto create_vertex_buffer(const resource_data initial_data, const usage usage = usage::default_use, const common::flags<cpu_access> cpu_access_flags = cpu_access::none)
        -> vertex_buffer_ref = 0;
    [[nodiscard]] virtual auto create_index_buffer(const resource_data initial_data, const usage usage = usage::default_use, const common::flags<cpu_access> cpu_access_flags = cpu_access::none)
        -> index_buffer_ref = 0;
    [[nodiscard]] virtual auto create_constant_buffer(const resource_data initial_data, const usage usage = usage::dynamic, const common::flags<cpu_access> cpu_access_flags = cpu_access::write)
        -> constant_buffer_ref = 0;

    [[nodiscard]] virtual auto create_texture2d(const math::size2d<imaging::image_view::dimensions_type> size, const std::uint32_t mip_levels, const format format,
                                                const texture_resource_data initial_data) -> texture2d_ref = 0;

    [[nodiscard]] virtual auto create_shader_resource_view(texture &texture) -> shader_resource_view_ref = 0;

    [[nodiscard]] virtual auto create_sampler_state(const sampler_state_settings &settings) -> sampler_state_ref = 0;

    [[nodiscard]] virtual auto create_bound_shader_state(const std::vector<input_layout_description> &input_layout, vertex_shader *vs, pixel_shader *ps) -> bound_shader_state_ref = 0;

    [[nodiscard]] virtual auto create_graphics_pipeline_state(const graphics_pipeline_state_initializer &initializer) -> graphics_pipeline_state_ref = 0;

    [[nodiscard]] virtual auto get_immediate_context() const noexcept -> context & = 0;

    [[nodiscard]] virtual auto get_dedicated_gpu_memory() const noexcept -> std::uint64_t = 0;

protected:
    device() noexcept = default;
};

} // namespace aeon::rhi

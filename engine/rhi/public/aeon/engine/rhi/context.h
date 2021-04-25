// Distributed under the BSD 2-Clause License - Copyright 2019-2021 Robin Degen

#pragma once

#include <aeon/engine/rhi/graphics_pipeline_state.h>
#include <aeon/engine/rhi/shader_resource_view.h>
#include <aeon/engine/rhi/shader.h>
#include <aeon/engine/rhi/buffer.h>
#include <aeon/engine/rhi/viewport.h>
#include <aeon/engine/rhi/texture.h>
#include <aeon/engine/rhi/sampler_state.h>
#include <aeon/engine/common/format.h>
#include <cstdint>

namespace aeon::engine::rhi
{

enum class map_mode
{
    read,
    write,
    read_write,
    write_discard,
    write_no_overwrite
};

class context
{
public:
    virtual ~context() = default;

    context(const context &) = delete;
    auto operator=(const context &) -> context & = delete;

    context(context &&) noexcept = delete;
    auto operator=(context &&) noexcept -> context & = delete;

    virtual void set_vertex_buffer(vertex_buffer &buffer, const std::uint32_t stride, const std::uint32_t offset = 0, const std::uint32_t slot = 0) = 0;
    virtual void set_index_buffer(index_buffer &buffer, const common::format format = common::format::r32_uint, const std::uint32_t offset = 0) = 0;

    virtual void set_shader_resource_view(graphics_shader &shader, const std::uint32_t index, shader_resource_view *view) = 0;
    virtual void set_shader_constant_buffer(graphics_shader &shader, const std::uint32_t index, constant_buffer *buffer) = 0;
    virtual void set_shader_sampler(graphics_shader &shader, const std::uint32_t index, sampler_state *sampler) = 0;

    [[nodiscard]] virtual void *map(vertex_buffer &resource, const map_mode map_mode = map_mode::write_discard) = 0;
    virtual void unmap(vertex_buffer &resource) = 0;

    [[nodiscard]] virtual void *map(index_buffer &resource, const map_mode map_mode = map_mode::write_discard) = 0;
    virtual void unmap(index_buffer &resource) = 0;

    [[nodiscard]] virtual void *map(constant_buffer &resource, const map_mode map_mode = map_mode::write_discard) = 0;
    virtual void unmap(constant_buffer &resource) = 0;

    [[nodiscard]] virtual void *map(texture2d &resource, const std::uint32_t sub_resource = 0, const map_mode map_mode = map_mode::write_discard) = 0;
    virtual void unmap(texture2d &resource, const std::uint32_t sub_resource = 0) = 0;

    virtual void set_viewport(const viewport &viewport) = 0;

    virtual void set_graphics_pipeline_state(graphics_pipeline_state &state) = 0;

    virtual void draw_indexed(const std::uint32_t index_count, const std::uint32_t index_offset, const std::int32_t base_vertex_offset) = 0;

protected:
    context() noexcept = default;
};

} // namespace aeon::engine::rhi

// Distributed under the BSD 2-Clause License - Copyright 2019-2021 Robin Degen

#pragma once

#include <aeon/rhi/blend_state.h>
#include <aeon/rhi/resource.h>
#include <aeon/rhi/bound_shader_state.h>
#include <aeon/rhi/depth_stencil_state.h>
#include <aeon/rhi/rasterizer_state.h>
#include <aeon/rhi/primitive_topology.h>

namespace aeon::rhi
{

struct graphics_pipeline_state_initializer final
{
    bound_shader_state *bound_shader_state = nullptr;
    blend_state *blend_state = nullptr;
    rasterizer_state *rasterizer_state = nullptr;
    depth_stencil_state *depth_stencil_state = nullptr;
    primitive_topology topology = primitive_topology::triangle_list;
};

class graphics_pipeline_state : public resource
{
public:
    ~graphics_pipeline_state() override = default;

    graphics_pipeline_state(const graphics_pipeline_state &) = delete;
    auto operator=(const graphics_pipeline_state &) -> graphics_pipeline_state & = delete;

    graphics_pipeline_state(graphics_pipeline_state &&) noexcept = delete;
    auto operator=(graphics_pipeline_state &&) noexcept -> graphics_pipeline_state & = delete;

    [[nodiscard]] virtual auto get_bound_shader_state() const noexcept -> bound_shader_state * = 0;
    [[nodiscard]] virtual auto get_blend_state() const noexcept -> blend_state * = 0;
    [[nodiscard]] virtual auto get_rasterizer_state() const noexcept -> rasterizer_state * = 0;
    [[nodiscard]] virtual auto get_depth_stencil_state() const noexcept -> depth_stencil_state * = 0;

    [[nodiscard]] auto topology() const noexcept -> primitive_topology
    {
        return topology_;
    }

protected:
    explicit graphics_pipeline_state(const primitive_topology topology) noexcept
        : resource{}
        , topology_{topology}
    {
    }

private:
    primitive_topology topology_;
};

using graphics_pipeline_state_ref = common::intrusive_ptr<graphics_pipeline_state>;

} // namespace aeon::rhi

// Distributed under the BSD 2-Clause License - Copyright 2019-2021 Robin Degen

#pragma once

#include "dx11_rhi_blend_state.h"
#include "dx11_rhi_bound_shader_state.h"
#include "dx11_rhi_depth_stencil_state.h"
#include "dx11_rhi_rasterizer_state.h"
#include <aeon/engine/rhi/graphics_pipeline_state.h>
#include <d3d11.h>
#include <wrl/client.h>

namespace aeon::engine::rhi::dx11
{

class dx11_rhi_graphics_pipeline_state final : public graphics_pipeline_state
{
public:
    explicit dx11_rhi_graphics_pipeline_state(dx11_rhi_bound_shader_state *bound_shader_state, dx11_rhi_blend_state *blend_state, dx11_rhi_rasterizer_state *rasterizer_state,
                                              dx11_rhi_depth_stencil_state *depth_stencil_state, const primitive_topology topology) noexcept
        : graphics_pipeline_state{topology}
        , bound_shader_state{bound_shader_state}
        , blend_state{blend_state}
        , rasterizer_state{rasterizer_state}
        , depth_stencil_state{depth_stencil_state}
    {
    }

    ~dx11_rhi_graphics_pipeline_state() final = default;

    dx11_rhi_graphics_pipeline_state(const dx11_rhi_graphics_pipeline_state &) = delete;
    auto operator=(const dx11_rhi_graphics_pipeline_state &) -> dx11_rhi_graphics_pipeline_state & = delete;

    dx11_rhi_graphics_pipeline_state(dx11_rhi_graphics_pipeline_state &&) noexcept = delete;
    auto operator=(dx11_rhi_graphics_pipeline_state &&) noexcept -> dx11_rhi_graphics_pipeline_state & = delete;

    [[nodiscard]] auto get_bound_shader_state() const noexcept -> rhi::bound_shader_state * final
    {
        return bound_shader_state.get();
    }

    [[nodiscard]] auto get_blend_state() const noexcept -> rhi::blend_state * final
    {
        return blend_state.get();
    }

    [[nodiscard]] auto get_rasterizer_state() const noexcept -> rhi::rasterizer_state * final
    {
        return rasterizer_state.get();
    }

    [[nodiscard]] auto get_depth_stencil_state() const noexcept -> rhi::depth_stencil_state * final
    {
        return depth_stencil_state.get();
    }

    aeon::common::intrusive_ptr<dx11_rhi_bound_shader_state> bound_shader_state;
    aeon::common::intrusive_ptr<dx11_rhi_blend_state> blend_state;
    aeon::common::intrusive_ptr<dx11_rhi_rasterizer_state> rasterizer_state;
    aeon::common::intrusive_ptr<dx11_rhi_depth_stencil_state> depth_stencil_state;

private:
    [[nodiscard]] auto native_impl_internal() noexcept -> void * final
    {
        return this;
    }
};

} // namespace aeon::engine::rhi::dx11

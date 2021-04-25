// Distributed under the BSD 2-Clause License - Copyright 2019-2021 Robin Degen

#pragma once

#include <aeon/engine/rhi/resource.h>

namespace aeon::engine::rhi
{

enum class fill_mode
{
    wireframe,
    solid
};

enum class cull_mode
{
    none,
    front,
    back,
};

enum class winding_order
{
    clockwise,
    counter_clockwise
};

struct rasterizer_state_initializer final
{
    fill_mode fill_mode = fill_mode::solid;
    cull_mode cull_mode = cull_mode::back;
    winding_order winding_order = winding_order::clockwise;

    int depth_bias = 0;
    float slope_scaled_depth_bias = 0.0f;
    float depth_bias_clamp = 0.0f;

    std::uint32_t depth_clip_enable : 1 = true;

    std::uint32_t scissor_enable : 1 = false;
    std::uint32_t multisample_enable : 1 = false;
    std::uint32_t antialiased_line_enable : 1 = false;
};

class rasterizer_state : public resource
{
public:
    ~rasterizer_state() override = default;

    rasterizer_state(const rasterizer_state &) = delete;
    auto operator=(const rasterizer_state &) -> rasterizer_state & = delete;

    rasterizer_state(rasterizer_state &&) noexcept = delete;
    auto operator=(rasterizer_state &&) noexcept -> rasterizer_state & = delete;

protected:
    explicit rasterizer_state() noexcept
        : resource{}
    {
    }
};

using rasterizer_state_ref = aeon::common::intrusive_ptr<rasterizer_state>;

} // namespace aeon::engine::rhi

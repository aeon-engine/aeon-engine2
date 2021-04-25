// Distributed under the BSD 2-Clause License - Copyright 2019-2021 Robin Degen

#pragma once

#include <aeon/engine/rhi/resource.h>

namespace aeon::engine::rhi
{

enum class depth_write_mask
{
    zero,
    all
};

enum class comparison_function
{
    never,
    less,
    equal,
    less_equal,
    greater,
    not_equal,
    greater_equal,
    always,
};

enum class stencil_op
{
    keep,
    zero,
    replace,
    increase_by_one_clamped,
    decrease_by_one_clamped,
    invert,
    increase_by_one_wrapped,
    decrease_by_one_wrapped,
};

struct depth_stencil_operation final
{
    stencil_op fail_operation = stencil_op::keep;
    stencil_op depth_fail_operation = stencil_op::keep;
    stencil_op pass_operation = stencil_op::keep;
    comparison_function function = comparison_function::always;
};

struct depth_stencil_state_initializer final
{
    depth_write_mask depth_write_mask = depth_write_mask::all;
    comparison_function depth_function = comparison_function::less;
    depth_stencil_operation front_face;
    depth_stencil_operation back_face;
    std::uint32_t depth_enable : 1 = true;
    std::uint32_t stencil_enable : 1 = false;
    std::uint8_t stencil_read_mask = 0;
    std::uint8_t stencil_write_mask = 0;
};

class depth_stencil_state : public resource
{
public:
    ~depth_stencil_state() override = default;

    depth_stencil_state(const depth_stencil_state &) = delete;
    auto operator=(const depth_stencil_state &) -> depth_stencil_state & = delete;

    depth_stencil_state(depth_stencil_state &&) noexcept = delete;
    auto operator=(depth_stencil_state &&) noexcept -> depth_stencil_state & = delete;

protected:
    explicit depth_stencil_state() noexcept
        : resource{}
    {
    }
};

using depth_stencil_state_ref = aeon::common::intrusive_ptr<depth_stencil_state>;

} // namespace aeon::engine::rhi

// Distributed under the BSD 2-Clause License - Copyright 2019-2021 Robin Degen

#pragma once

#include <aeon/engine/rhi/resource.h>

namespace aeon::engine::rhi
{

enum class blend_factor
{
    zero,
    one,
    src_color,
    inv_src_color,
    src_alpha,
    inv_src_alpha,
    dest_alpha,
    inv_dest_alpha,
    dest_color,
    inv_dest_color,
    src_alpha_sat,
    constant_blend_factor,
    inv_blend_factor,
    src1_color,
    inv_src1_color,
    src1_alpha,
    inv_src1_alpha,
};

enum class blend_operation
{
    add,
    subtract,
    rev_subtract,
    min,
    max,
};

struct blend_state_initializer final
{
    std::uint32_t enable_alpha_to_coverage : 1 = false;
    std::uint32_t enable_independent_blend : 1 = false;
    std::uint32_t enable_blend : 1 = false;

    blend_factor source_blend = blend_factor::one;
    blend_factor destination_blend = blend_factor::zero;
    blend_operation operation = blend_operation::add;
    blend_factor source_alpha_blend = blend_factor::one;
    blend_factor destination_alpha_blend = blend_factor::zero;
    blend_operation alpha_operation = blend_operation::add;
};

class blend_state : public resource
{
public:
    ~blend_state() override = default;

    blend_state(const blend_state &) = delete;
    auto operator=(const blend_state &) -> blend_state & = delete;

    blend_state(blend_state &&) noexcept = delete;
    auto operator=(blend_state &&) noexcept -> blend_state & = delete;

protected:
    explicit blend_state() noexcept
        : resource{}
    {
    }
};

using blend_state_ref = aeon::common::intrusive_ptr<blend_state>;

} // namespace aeon::engine::rhi

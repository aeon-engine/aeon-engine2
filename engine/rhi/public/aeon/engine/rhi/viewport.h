// Distributed under the BSD 2-Clause License - Copyright 2019-2021 Robin Degen

#pragma once

#include <aeon/math/rectangle.h>
#include <aeon/math/range.h>

namespace aeon::engine::rhi
{

struct viewport final
{
    math::rectangle<float> rectangle{};
    math::range<float> depth{0.0f, 1.0f};
};

} // namespace aeon::engine::rhi

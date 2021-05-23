// Distributed under the BSD 2-Clause License - Copyright 2019-2021 Robin Degen

#pragma once

#include <aeon/math/vector3.h>
#include <aeon/math/vector2.h>

namespace aeon::engine::core::types
{

struct vertex_data
{
    math::vector3<float> position;
    math::vector2<float> uv;
    math::vector3<float> normal;
    math::vector3<float> tangent;
    math::vector3<float> bitangent;
};

} // namespace aeon::engine::core::types

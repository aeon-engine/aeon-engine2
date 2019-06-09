// Distributed under the BSD 2-Clause License - Copyright 2019-2021 Robin Degen

#pragma once

#include <aeon/rhi/format.h>
#include <cstdint>
#include <string>

namespace aeon::rhi
{

struct input_layout_description final
{
    std::string name;
    format format = format::r32g32b32a32_float;
    std::uint32_t stride = 0;
};

} // namespace aeon::rhi

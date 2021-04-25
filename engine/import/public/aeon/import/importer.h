// Distributed under the BSD 2-Clause License - Copyright 2019-2021 Robin Degen

#pragma once

#include <aeon/resources/export.h>

namespace aeon::renderer
{

class AEON_ENGINE_RESOURCES_EXPORT mesh
{
public:
    mesh();
    ~mesh();

    mesh(const mesh &) = delete;
    auto operator=(const mesh &) -> mesh & = delete;

    mesh(mesh &&) noexcept = delete;
    auto operator=(mesh &&) noexcept -> mesh & = delete;
};

} // namespace aeon::renderer

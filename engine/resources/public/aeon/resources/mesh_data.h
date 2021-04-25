// Distributed under the BSD 2-Clause License - Copyright 2019-2021 Robin Degen

#pragma once

#include <aeon/resources/export.h>
#include <aeon/math/vector3.h>
#include <aeon/math/vector2.h>
#include <vector>
#include <cstdint>

namespace aeon::resources
{

struct vertex_data
{
    math::vector3<float> position;
    math::vector2<float> uv;
    math::vector3<float> normal;
    math::vector3<float> tangent;
    math::vector3<float> bitangent;
};

class AEON_ENGINE_RESOURCES_EXPORT mesh_data
{
public:
    using vertex_type = vertex_data;
    using index_type = std::uint32_t;

    explicit mesh_data(std::vector<vertex_type> vertices, std::vector<index_type> indices) noexcept;
    ~mesh_data();

    mesh_data(const mesh_data &) = delete;
    auto operator=(const mesh_data &) -> mesh_data & = delete;

    mesh_data(mesh_data &&) noexcept = delete;
    auto operator=(mesh_data &&) noexcept -> mesh_data & = delete;

    [[nodiscard]] auto vertices() const noexcept -> const std::vector<vertex_type> &;
    [[nodiscard]] auto indices() const noexcept -> const std::vector<index_type> &;

private:
    std::vector<vertex_type> vertices_;
    std::vector<index_type> indices_;
};

} // namespace aeon::resources

// Distributed under the BSD 2-Clause License - Copyright 2019-2021 Robin Degen

#include <aeon/resources/mesh_data.h>

namespace aeon::resources
{

mesh_data::mesh_data(std::vector<vertex_type> vertices, std::vector<index_type> indices) noexcept
    : vertices_{std::move(vertices)}
    , indices_{std::move(indices)}
{
}

mesh_data::~mesh_data() = default;

auto mesh_data::vertices() const noexcept -> const std::vector<vertex_type> &
{
    return vertices_;
}

auto mesh_data::indices() const noexcept -> const std::vector<index_type> &
{
    return indices_;
}

} // namespace aeon::resources

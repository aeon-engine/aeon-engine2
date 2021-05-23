// Distributed under the BSD 2-Clause License - Copyright 2019-2021 Robin Degen

#include <aeon/engine/resources/mesh_data.h>

namespace aeon::engine::resources
{

mesh_data::mesh_data(std::vector<vertex_type> vertices, std::vector<index_type> indices, const resource_id material_id) noexcept
    : resource_data{}
    , vertices_{std::move(vertices)}
    , indices_{std::move(indices)}
    , material_id_{material_id}
{
}

mesh_data::mesh_data(const resource_id id, std::vector<vertex_type> vertices, std::vector<index_type> indices, const resource_id material_id) noexcept
    : resource_data{id}
    , vertices_{std::move(vertices)}
    , indices_{std::move(indices)}
    , material_id_{material_id}
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

auto mesh_data::material_id() const noexcept -> resource_id
{
    return material_id_;
}

auto mesh_data::dependencies() const noexcept -> std::set<resource_id>
{
    std::set<resource_id> resources;
    resources.insert(material_id_);
    return resources;
}

} // namespace aeon::engine::resources

// Distributed under the BSD 2-Clause License - Copyright 2019-2021 Robin Degen

#include <aeon/engine/resources/scene_prefab_data.h>

namespace aeon::engine::resources
{

namespace internal
{

void add_dependencies(std::set<resource_data::resource_id> &dependencies, const scene_node_data &node)
{
    for (const auto &id : node.component_ids())
    {
        dependencies.insert(id);
    }

    for (const auto &child : node.children())
    {
        add_dependencies(dependencies, *child);
    }
}

} // namespace internal

scene_prefab_data::scene_prefab_data(std::string name, std::pmr::memory_resource *allocator) noexcept
    : resource_data{}
    , root_{common::pmr::make_unique<scene_node_data>(allocator, std::move(name), math::mat4::indentity(), allocator)}
{
}

scene_prefab_data::scene_prefab_data(const resource_id id, std::string name, std::pmr::memory_resource *allocator) noexcept
    : resource_data{id}
    , root_{common::pmr::make_unique<scene_node_data>(allocator, std::move(name), math::mat4::indentity(), allocator)}
{
}

scene_prefab_data::~scene_prefab_data() = default;

auto scene_prefab_data::root() noexcept -> scene_node_data &
{
    return *root_;
}

auto scene_prefab_data::root() const noexcept -> const scene_node_data &
{
    return *root_;
}

auto scene_prefab_data::dependencies() const noexcept -> std::set<resource_id>
{
    std::set<resource_id> dependencies;
    internal::add_dependencies(dependencies, *root_);
    return dependencies;
}

} // namespace aeon::engine::resources

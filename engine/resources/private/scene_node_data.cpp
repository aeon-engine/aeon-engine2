// Distributed under the BSD 2-Clause License - Copyright 2019-2021 Robin Degen

#include <aeon/engine/resources/scene_node_data.h>

namespace aeon::engine::resources
{

scene_node_data::scene_node_data(std::string name, const math::mat4 &transform, std::pmr::memory_resource *allocator) noexcept
    : parent_{nullptr}
    , transform_{transform}
    , name_{std::move(name)}
    , components_{allocator}
    , children_{allocator}
{
}

scene_node_data::~scene_node_data() = default;

auto scene_node_data::get_allocator() const noexcept -> std::pmr::memory_resource *
{
    return children_.get_allocator().resource();
}

auto scene_node_data::has_parent() const noexcept -> bool
{
    return parent_ != nullptr;
}

auto scene_node_data::parent() const noexcept -> scene_node_data *
{
    return parent_;
}

auto scene_node_data::transform() const noexcept -> const math::mat4 &
{
    return transform_;
}

auto scene_node_data::name() const noexcept -> const std::string &
{
    return name_;
}

auto scene_node_data::component_ids() const noexcept -> const std::pmr::vector<resource_data::resource_id> &
{
    return components_;
}

void scene_node_data::add_component(const resource_data::resource_id id)
{
    components_.push_back(id);
}

auto scene_node_data::children() const noexcept -> const std::pmr::vector<common::pmr::unique_ptr<scene_node_data>> &
{
    return children_;
}

auto scene_node_data::add_child(std::string name, const math::mat4 &transform) -> scene_node_data &
{
    auto &child = children_.emplace_back(common::pmr::make_unique<scene_node_data>(get_allocator(), std::move(name), transform, get_allocator()));
    child->parent_ = this;
    return *child;
}

} // namespace aeon::engine::resources

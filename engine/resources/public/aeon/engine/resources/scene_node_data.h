// Distributed under the BSD 2-Clause License - Copyright 2019-2021 Robin Degen

#pragma once

#include <aeon/engine/resources/export.h>
#include <aeon/engine/resources/resource_data.h>
#include <aeon/math/mat4.h>
#include <aeon/common/pmr.h>
#include <string>

namespace aeon::engine::resources
{

class AEON_ENGINE_RESOURCES_EXPORT scene_node_data final
{
public:
    explicit scene_node_data(std::string name, const math::mat4 &transform = math::mat4::indentity(), std::pmr::memory_resource *allocator = std::pmr::get_default_resource()) noexcept;
    ~scene_node_data();

    scene_node_data(const scene_node_data &) = delete;
    auto operator=(const scene_node_data &) -> scene_node_data & = delete;

    scene_node_data(scene_node_data &&) noexcept = default;
    auto operator=(scene_node_data &&) noexcept -> scene_node_data & = default;

    [[nodiscard]] auto get_allocator() const noexcept -> std::pmr::memory_resource *;

    [[nodiscard]] auto has_parent() const noexcept -> bool;

    [[nodiscard]] auto parent() const noexcept -> scene_node_data *;

    [[nodiscard]] auto transform() const noexcept -> const math::mat4 &;

    [[nodiscard]] auto name() const noexcept -> const std::string &;

    [[nodiscard]] auto component_ids() const noexcept -> const std::pmr::vector<resource_data::resource_id> &;

    void add_component(const resource_data::resource_id id);

    [[nodiscard]] auto children() const noexcept -> const std::pmr::vector<aeon::common::pmr::unique_ptr<scene_node_data>> &;

    [[nodiscard]] auto add_child(std::string name, const math::mat4 &transform) -> scene_node_data &;

private:
    scene_node_data *parent_;

    math::mat4 transform_;
    std::string name_;

    std::pmr::vector<resource_data::resource_id> components_;
    std::pmr::vector<aeon::common::pmr::unique_ptr<scene_node_data>> children_;
};

} // namespace aeon::engine::resources

// Distributed under the BSD 2-Clause License - Copyright 2019-2021 Robin Degen

#pragma once

#include <aeon/engine/resources/resource_data.h>
#include <aeon/engine/resources/scene_node_data.h>
#include <aeon/engine/resources/export.h>

namespace aeon::engine::resources
{

class AEON_ENGINE_RESOURCES_EXPORT scene_prefab_data final : public resource_data
{
public:
    explicit scene_prefab_data(std::string name, std::pmr::memory_resource *allocator = std::pmr::get_default_resource()) noexcept;
    explicit scene_prefab_data(const resource_id id, std::string name, std::pmr::memory_resource *allocator = std::pmr::get_default_resource()) noexcept;
    ~scene_prefab_data() final;

    scene_prefab_data(const scene_prefab_data &) = delete;
    auto operator=(const scene_prefab_data &) -> scene_prefab_data & = delete;

    scene_prefab_data(scene_prefab_data &&) noexcept = default;
    auto operator=(scene_prefab_data &&) noexcept -> scene_prefab_data & = default;

    [[nodiscard]] auto root() noexcept -> scene_node_data &;

    [[nodiscard]] auto root() const noexcept -> const scene_node_data &;

    [[nodiscard]] auto dependencies() const noexcept -> std::set<resource_id> final;

private:
    aeon::common::pmr::unique_ptr<scene_node_data> root_;
};

} // namespace aeon::engine::resources

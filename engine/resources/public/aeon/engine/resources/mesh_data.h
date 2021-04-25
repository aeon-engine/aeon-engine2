// Distributed under the BSD 2-Clause License - Copyright 2019-2021 Robin Degen

#pragma once

#include <aeon/engine/resources/resource_data.h>
#include <aeon/engine/resources/export.h>
#include <aeon/engine/common/vertex_data.h>
#include <vector>
#include <cstdint>

namespace aeon::engine::resources
{

class AEON_ENGINE_RESOURCES_EXPORT mesh_data final : public resource_data
{
public:
    using vertex_type = common::vertex_data;
    using index_type = std::uint32_t;

    explicit mesh_data(std::vector<vertex_type> vertices, std::vector<index_type> indices, const resource_id material_id) noexcept;
    explicit mesh_data(const resource_id id, std::vector<vertex_type> vertices, std::vector<index_type> indices, const resource_id material_id) noexcept;
    ~mesh_data() final;

    mesh_data(const mesh_data &) = delete;
    auto operator=(const mesh_data &) -> mesh_data & = delete;

    mesh_data(mesh_data &&) noexcept = default;
    auto operator=(mesh_data &&) noexcept -> mesh_data & = default;

    [[nodiscard]] auto vertices() const noexcept -> const std::vector<vertex_type> &;
    [[nodiscard]] auto indices() const noexcept -> const std::vector<index_type> &;
    [[nodiscard]] auto material_id() const noexcept -> const resource_id &;

    [[nodiscard]] auto dependencies() const noexcept -> std::vector<resource_id> final;

private:
    std::vector<vertex_type> vertices_;
    std::vector<index_type> indices_;
    resource_id material_id_;
};

} // namespace aeon::engine::resources

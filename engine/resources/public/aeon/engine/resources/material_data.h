// Distributed under the BSD 2-Clause License - Copyright 2019-2021 Robin Degen

#pragma once

#include <aeon/engine/resources/resource_data.h>
#include <aeon/engine/resources/export.h>

namespace aeon::engine::resources
{

class AEON_ENGINE_RESOURCES_EXPORT material_data final : public resource_data
{
public:
    explicit material_data(const resource_id albedo_texture_id, const resource_id normal_texture_id, const resource_id roughness_texture_id, const resource_id metalness_texture_id,
                           const resource_id specular_texture_id, const resource_id displacement_texture_id, const resource_id ambient_occlusion_texture_id, const resource_id refraction_texture_id,
                           const resource_id emissive_texture_id, std::pmr::memory_resource *allocator = std::pmr::get_default_resource()) noexcept;
    explicit material_data(const resource_id id, const resource_id albedo_texture_id, const resource_id normal_texture_id, const resource_id roughness_texture_id,
                           const resource_id metalness_texture_id, const resource_id specular_texture_id, const resource_id displacement_texture_id, const resource_id ambient_occlusion_texture_id,
                           const resource_id refraction_texture_id, const resource_id emissive_texture_id, std::pmr::memory_resource *allocator = std::pmr::get_default_resource()) noexcept;
    ~material_data() final;

    material_data(const material_data &) = delete;
    auto operator=(const material_data &) -> material_data & = delete;

    material_data(material_data &&) noexcept = default;
    auto operator=(material_data &&) noexcept -> material_data & = default;

    [[nodiscard]] auto albedo_texture_id() const noexcept -> resource_id;
    [[nodiscard]] auto normal_texture_id() const noexcept -> resource_id;
    [[nodiscard]] auto roughness_texture_id() const noexcept -> resource_id;
    [[nodiscard]] auto metalness_texture_id() const noexcept -> resource_id;
    [[nodiscard]] auto specular_texture_id() const noexcept -> resource_id;
    [[nodiscard]] auto displacement_texture_id() const noexcept -> resource_id;
    [[nodiscard]] auto ambient_occlusion_texture_id() const noexcept -> resource_id;
    [[nodiscard]] auto refraction_texture_id() const noexcept -> resource_id;
    [[nodiscard]] auto emissive_texture_id() const noexcept -> resource_id;

    [[nodiscard]] auto dependencies() const noexcept -> std::pmr::set<resource_id> final;

private:
    const resource_id albedo_texture_id_; // diffuse, base color, optionally combined with opacity through alpha
    const resource_id normal_texture_id_;
    const resource_id roughness_texture_id_; // inverse of glossiness
    const resource_id metalness_texture_id_;
    const resource_id specular_texture_id_;
    const resource_id displacement_texture_id_; // "height"
    const resource_id ambient_occlusion_texture_id_;
    const resource_id refraction_texture_id_;
    const resource_id emissive_texture_id_; // "Self-illumination"
};

} // namespace aeon::engine::resources

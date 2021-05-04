// Distributed under the BSD 2-Clause License - Copyright 2019-2021 Robin Degen

#include <aeon/engine/resources/material_data.h>

namespace aeon::engine::resources
{

material_data::material_data(const resource_id albedo_texture_id, const resource_id normal_texture_id, const resource_id roughness_texture_id, const resource_id metalness_texture_id,
                             const resource_id specular_texture_id, const resource_id displacement_texture_id, const resource_id ambient_occlusion_texture_id, const resource_id refraction_texture_id,
                             const resource_id emissive_texture_id, std::pmr::memory_resource *allocator) noexcept
    : resource_data{allocator}
    , albedo_texture_id_{albedo_texture_id}
    , normal_texture_id_{normal_texture_id}
    , roughness_texture_id_{roughness_texture_id}
    , metalness_texture_id_{metalness_texture_id}
    , specular_texture_id_{specular_texture_id}
    , displacement_texture_id_{displacement_texture_id}
    , ambient_occlusion_texture_id_{ambient_occlusion_texture_id}
    , refraction_texture_id_{refraction_texture_id}
    , emissive_texture_id_{emissive_texture_id}

{
}

material_data::material_data(const resource_id id, const resource_id albedo_texture_id, const resource_id normal_texture_id, const resource_id roughness_texture_id,
                             const resource_id metalness_texture_id, const resource_id specular_texture_id, const resource_id displacement_texture_id, const resource_id ambient_occlusion_texture_id,
                             const resource_id refraction_texture_id, const resource_id emissive_texture_id, std::pmr::memory_resource *allocator) noexcept
    : resource_data{id, allocator}
    , albedo_texture_id_{albedo_texture_id}
    , normal_texture_id_{normal_texture_id}
    , roughness_texture_id_{roughness_texture_id}
    , metalness_texture_id_{metalness_texture_id}
    , specular_texture_id_{specular_texture_id}
    , displacement_texture_id_{displacement_texture_id}
    , ambient_occlusion_texture_id_{ambient_occlusion_texture_id}
    , refraction_texture_id_{refraction_texture_id}
    , emissive_texture_id_{emissive_texture_id}
{
}

material_data::~material_data() = default;

auto material_data::albedo_texture_id() const noexcept -> resource_id
{
    return albedo_texture_id_;
}

auto material_data::normal_texture_id() const noexcept -> resource_id
{
    return normal_texture_id_;
}

auto material_data::roughness_texture_id() const noexcept -> resource_id
{
    return roughness_texture_id_;
}

auto material_data::metalness_texture_id() const noexcept -> resource_id
{
    return metalness_texture_id_;
}

auto material_data::specular_texture_id() const noexcept -> resource_id
{
    return specular_texture_id_;
}

auto material_data::displacement_texture_id() const noexcept -> resource_id
{
    return displacement_texture_id_;
}

auto material_data::ambient_occlusion_texture_id() const noexcept -> resource_id
{
    return ambient_occlusion_texture_id_;
}

auto material_data::refraction_texture_id() const noexcept -> resource_id
{
    return refraction_texture_id_;
}

auto material_data::emissive_texture_id() const noexcept -> resource_id
{
    return emissive_texture_id_;
}

auto material_data::dependencies() const noexcept -> std::pmr::set<resource_id>
{
    std::pmr::set<resource_id> dependencies{get_allocator()};

    if (albedo_texture_id_)
        dependencies.insert(albedo_texture_id_);

    if (normal_texture_id_)
        dependencies.insert(normal_texture_id_);

    if (roughness_texture_id_)
        dependencies.insert(roughness_texture_id_);

    if (metalness_texture_id_)
        dependencies.insert(metalness_texture_id_);

    if (specular_texture_id_)
        dependencies.insert(specular_texture_id_);

    if (displacement_texture_id_)
        dependencies.insert(displacement_texture_id_);

    if (ambient_occlusion_texture_id_)
        dependencies.insert(ambient_occlusion_texture_id_);

    if (refraction_texture_id_)
        dependencies.insert(refraction_texture_id_);

    if (emissive_texture_id_)
        dependencies.insert(emissive_texture_id_);

    return dependencies;
}

} // namespace aeon::engine::resources

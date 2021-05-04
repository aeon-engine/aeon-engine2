// Distributed under the BSD 2-Clause License - Copyright 2019-2021 Robin Degen

#pragma once

#include <aeon/engine/resources/material_data.h>
#include <aeon/engine/resources/mesh_data.h>
#include <aeon/engine/resources/texture_data.h>
#include <aeon/engine/resources/scene_prefab_data.h>
#include <aeon/common/pmr.h>
#include <vector>

namespace aeon::engine::import
{

struct import_result
{
    std::pmr::vector<aeon::common::pmr::unique_ptr<resources::texture_data>> textures;
    std::pmr::vector<aeon::common::pmr::unique_ptr<resources::material_data>> materials;
    std::pmr::vector<aeon::common::pmr::unique_ptr<resources::mesh_data>> meshes;
    std::pmr::vector<aeon::common::pmr::unique_ptr<resources::scene_prefab_data>> prefabs;
};

} // namespace aeon::engine::import

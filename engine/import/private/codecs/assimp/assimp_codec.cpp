// Distributed under the BSD 2-Clause License - Copyright 2019-2021 Robin Degen

#include "assimp_codec.h"
#include <aeon/streams/stream_reader.h>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

namespace aeon::engine::import::codecs
{

namespace internal
{

void import_materials(const aiScene *scene, std::pmr::memory_resource *allocator)
{
    // aiTextureType_BASE_COLOR = 12,
    // aiTextureType_NORMAL_CAMERA = 13,
    // aiTextureType_EMISSION_COLOR = 14,
    // aiTextureType_METALNESS = 15,
    // aiTextureType_DIFFUSE_ROUGHNESS = 16,
    // aiTextureType_AMBIENT_OCCLUSION = 17,
    for (auto i = 0ul; i < scene->mNumMaterials; ++i)
    {
        const auto ai_material = scene->mMaterials[i];
        auto ai_texture_path = aiString{};

        ai_material->GetTexture(


        if (ai_material->GetTexture(aiTextureType_DIFFUSE, 0, &ai_texture_path) == AI_SUCCESS)
        {
            auto texture_path = ai_texture_path.data;
            mesh_ref.add_material(texture_path);
        }
        else
        {
            AEON_LOG_ERROR(logger_) << "Could not get diffuse texture for material. Ignoring." << std::endl;
            // TODO: How to handle this?
            mesh_ref.add_material("/resources/materials/test.amf");
        }
    }
}

} // namespace internal

assimp_codec::assimp_codec() = default;

assimp_codec::~assimp_codec() = default;

auto assimp_codec::import_multi(const streams::idynamic_stream &stream, std::pmr::memory_resource *allocator) -> import_result
{
    const streams::stream_reader reader{stream};
    auto input = reader.read_to_vector<std::byte>();

    const auto scene = importer_.ReadFileFromMemory(std::data(input), std::size(input), aiProcessPreset_TargetRealtime_Quality);

    if (!scene)
        throw std::runtime_error{"ERROR"}; // TODO

    return {};
}

auto assimp_codec::supports_format(const std::string &extension) const noexcept -> format_type
{
    if (importer_.IsExtensionSupported(extension))
        return format_type::multi;

    return format_type::unsupported;
}

} // namespace aeon::engine::import::codecs

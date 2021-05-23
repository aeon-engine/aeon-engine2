// Distributed under the BSD 2-Clause License - Copyright 2019-2021 Robin Degen

#include "importer_impl.h"
#include "codecs/assimp/assimp_codec.h"
#include <aeon/engine/core/hal/file_manager.h>
#include <aeon/streams/devices/file_device.h>
#include <aeon/streams/dynamic_stream.h>

namespace aeon::engine::import
{

[[nodiscard]] AEON_ENGINE_IMPORT_EXPORT auto importer::create() -> std::unique_ptr<importer>
{
    return std::make_unique<importer_impl>();
}

importer_impl::importer_impl() noexcept
{
    codecs_.push_back(std::make_unique<codecs::assimp_codec>());
}

importer_impl::~importer_impl() = default;

auto importer_impl::import(const core::types::path &path) -> import_result
{
    const auto extension = core::hal::file_manager::get().file_extension(path);

    for (auto &codec : codecs_)
    {
        switch (const auto support_type = codec->format_support_type(extension); support_type)
        {
            case codecs::format_type::unsupported:
                continue;
            case codecs::format_type::texture:
            {
                import_result result;
                result.textures.push_back(codec->import_texture(path));
                return result;
            }
            case codecs::format_type::multi:
            {
                return codec->import_multi(path);
            }
        }
    }

    // TODO
    throw std::runtime_error{"Unsupported."};
}

} // namespace aeon::engine::import

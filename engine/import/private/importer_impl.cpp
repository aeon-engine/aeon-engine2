// Distributed under the BSD 2-Clause License - Copyright 2019-2021 Robin Degen

#include "importer_impl.h"
#include "codecs/assimp/assimp_codec.h"

namespace aeon::engine::import
{

AEON_ENGINE_IMPORT_EXPORT [[nodiscard]] auto importer::create(std::pmr::memory_resource *allocator) -> std::unique_ptr<importer>
{
    return std::make_unique<importer_impl>(allocator);
}

importer_impl::importer_impl(std::pmr::memory_resource *allocator) noexcept
{
    codecs_.push_back(std::make_unique<codecs::assimp_codec>());
}

importer_impl::~importer_impl() = default;

auto importer_impl::import(const std::filesystem::path &path, std::pmr::memory_resource *allocator) -> import_result
{
    const auto extension = path.extension().string();

    for (auto &codec : codecs_)
    {
        if (codec->supports_format(extension))
            return codec->import(path, allocator);
    }

    // TODO
    throw std::runtime_error{"Unsupported."};
}

} // namespace aeon::engine::import

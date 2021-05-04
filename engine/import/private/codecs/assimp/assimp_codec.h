// Distributed under the BSD 2-Clause License - Copyright 2019-2021 Robin Degen

#pragma once

#include "codecs/codec.h"
#include <assimp/Importer.hpp>

namespace aeon::engine::import::codecs
{

class assimp_codec final : public codec
{
public:
    assimp_codec();
    ~assimp_codec() final;

    assimp_codec(const assimp_codec &) = delete;
    auto operator=(const assimp_codec &) -> codec & = delete;

    assimp_codec(assimp_codec &&) noexcept = delete;
    auto operator=(assimp_codec &&) noexcept -> assimp_codec & = delete;

    [[nodiscard]] auto import_multi(const streams::idynamic_stream &stream, std::pmr::memory_resource *allocator = std::pmr::get_default_resource()) -> import_result final;

    [[nodiscard]] auto supports_format(const std::string &extension) const noexcept -> format_type final;

private:
    Assimp::Importer importer_;
};

} // namespace aeon::engine::import::codecs

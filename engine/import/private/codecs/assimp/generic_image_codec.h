// Distributed under the BSD 2-Clause License - Copyright 2019-2021 Robin Degen

#pragma once

#include "codecs/codec.h"

namespace aeon::engine::import::codecs
{

class generic_image_codec final : public codec
{
public:
    generic_image_codec();
    ~generic_image_codec() final;

    generic_image_codec(const generic_image_codec &) = delete;
    auto operator=(const generic_image_codec &) -> codec & = delete;

    generic_image_codec(generic_image_codec &&) noexcept = delete;
    auto operator=(generic_image_codec &&) noexcept -> generic_image_codec & = delete;

    [[nodiscard]] auto import_texture(const core::types::path &path) -> aeon::common::pmr::unique_ptr<resources::texture_data> final;

    [[nodiscard]] auto format_support_type(const std::u8string &extension) const noexcept -> format_type final;
};

} // namespace aeon::engine::import::codecs

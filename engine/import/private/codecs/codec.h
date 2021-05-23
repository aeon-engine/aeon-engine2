// Distributed under the BSD 2-Clause License - Copyright 2019-2021 Robin Degen

#pragma once

#include <aeon/engine/import/import_result.h>
#include <aeon/engine/core/hal/file_manager.h>

namespace aeon::engine::import::codecs
{

enum class format_type
{
    unsupported,
    texture,
    multi
};

class codec
{
public:
    virtual ~codec() = default;

    codec(const codec &) = delete;
    auto operator=(const codec &) -> codec & = delete;

    codec(codec &&) noexcept = delete;
    auto operator=(codec &&) noexcept -> codec & = delete;

    [[nodiscard]] virtual auto import_texture([[maybe_unused]] const core::types::path &path) -> aeon::common::pmr::unique_ptr<resources::texture_data>
    {
        throw std::runtime_error{"Unsupported for this format."};
    }

    [[nodiscard]] virtual auto import_multi([[maybe_unused]] const core::types::path &path) -> import_result
    {
        throw std::runtime_error{"Unsupported for this format."};
    }

    [[nodiscard]] virtual auto format_support_type(const std::u8string &extension) const noexcept -> format_type = 0;

protected:
    codec() noexcept = default;
};

} // namespace aeon::engine::import::codecs

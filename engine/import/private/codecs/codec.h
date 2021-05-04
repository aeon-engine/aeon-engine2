// Distributed under the BSD 2-Clause License - Copyright 2019-2021 Robin Degen

#pragma once

#include <aeon/engine/import/import_result.h>
#include <aeon/streams/idynamic_stream.h>
#include <filesystem>

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

    [[nodiscard]] virtual auto import_texture(const streams::idynamic_stream &stream, std::pmr::memory_resource *allocator = std::pmr::get_default_resource())
        -> aeon::common::pmr::unique_ptr<resources::texture_data>
    {
        throw std::runtime_error{"Unsupported for this format."};
    }

    [[nodiscard]] virtual auto import_multi(const streams::idynamic_stream &stream, std::pmr::memory_resource *allocator = std::pmr::get_default_resource()) -> import_result
    {
        throw std::runtime_error{"Unsupported for this format."};
    }

    [[nodiscard]] virtual auto supports_format(const std::string &extension) const noexcept -> format_type = 0;

protected:
    codec() noexcept = default;
};

} // namespace aeon::engine::import::codecs

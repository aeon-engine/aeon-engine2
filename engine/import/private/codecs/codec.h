// Distributed under the BSD 2-Clause License - Copyright 2019-2021 Robin Degen

#pragma once

#include <filesystem>

namespace aeon::import::codecs
{

struct import_result
{
};

class codec
{
public:
    virtual ~codec() = default;

    codec(const codec &) = delete;
    auto operator=(const codec &) -> codec & = delete;

    codec(codec &&) noexcept = delete;
    auto operator=(codec &&) noexcept -> codec & = delete;

    [[nodiscard]] virtual auto import(const std::filesystem::path &path) -> void * = 0;

protected:
    codec() noexcept = default;
};

} // namespace aeon::import::codecs

// Distributed under the BSD 2-Clause License - Copyright 2019-2021 Robin Degen

#pragma once

#include <aeon/engine/core/types/path.h>
#include <aeon/engine/core/export.h>
#include <aeon/streams/dynamic_stream.h>

namespace aeon::engine::core::hal
{

class file_manager
{
public:
    [[nodiscard]] AEON_ENGINE_CORE_EXPORT static auto get() noexcept -> file_manager &;

    file_manager(const file_manager &) = delete;
    auto operator=(const file_manager &) -> file_manager & = delete;

    file_manager(file_manager &&) noexcept = delete;
    auto operator=(file_manager &&) noexcept -> file_manager & = delete;

    [[nodiscard]] virtual auto open_read(const types::path &path) const -> std::unique_ptr<streams::idynamic_stream> = 0;

    [[nodiscard]] virtual auto open_write(const types::path &path) const -> std::unique_ptr<streams::idynamic_stream> = 0;

    [[nodiscard]] virtual auto exists(const types::path &path) const noexcept -> bool = 0;

    [[nodiscard]] virtual auto absolute_path(const types::path &path) const noexcept -> types::path = 0;

    [[nodiscard]] virtual auto absolute_path(const types::path &base_path, const types::path &path) const noexcept -> types::path = 0;

    [[nodiscard]] virtual auto file_extension(const types::path &path) const noexcept -> std::u8string = 0;

protected:
    file_manager() = default;
    virtual ~file_manager() = default;
};

} // namespace aeon::engine::core::hal

// Distributed under the BSD 2-Clause License - Copyright 2019-2021 Robin Degen

#pragma once

#include <aeon/engine/core/hal/file_manager.h>

namespace aeon::engine::core::hal
{

class default_file_manager final : public file_manager
{
public:
    default_file_manager();
    ~default_file_manager() final;

    default_file_manager(const default_file_manager &) = delete;
    auto operator=(const default_file_manager &) -> default_file_manager & = delete;

    default_file_manager(default_file_manager &&) noexcept = delete;
    auto operator=(default_file_manager &&) noexcept -> default_file_manager & = delete;

    [[nodiscard]] auto open_read(const types::path &path) const -> std::unique_ptr<streams::idynamic_stream> final;

    [[nodiscard]] auto open_write(const types::path &path) const -> std::unique_ptr<streams::idynamic_stream> final;

    [[nodiscard]] auto exists(const types::path &path) const noexcept -> bool final;

    [[nodiscard]] auto absolute_path(const types::path &path) const noexcept -> types::path final;

    [[nodiscard]] auto absolute_path(const types::path &base_path, const types::path &path) const noexcept -> types::path final;

    [[nodiscard]] auto file_extension(const types::path &path) const noexcept -> std::u8string final;
};

} // namespace aeon::engine::core::hal

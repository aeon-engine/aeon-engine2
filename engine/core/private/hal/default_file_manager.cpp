// Distributed under the BSD 2-Clause License - Copyright 2019-2021 Robin Degen

#include "default_file_manager.h"
#include <aeon/streams/devices/file_device.h>
#include <aeon/common/path.h>

namespace aeon::engine::core::hal
{

default_file_manager::default_file_manager() = default;
default_file_manager::~default_file_manager() = default;

auto default_file_manager::open_read(const types::path &path) const -> std::unique_ptr<streams::idynamic_stream>
{
    return streams::make_dynamic_stream_ptr(streams::file_source_device{path});
}

auto default_file_manager::open_write(const types::path &path) const -> std::unique_ptr<streams::idynamic_stream>
{
    return streams::make_dynamic_stream_ptr(streams::file_sink_device{path});
}

auto default_file_manager::exists(const types::path &path) const noexcept -> bool
{
    std::error_code ec;
    const auto result = std::filesystem::exists(path, ec);
    return !ec && result;
}

auto default_file_manager::absolute_path(const types::path &path) const noexcept -> types::path
{
    return std::filesystem::weakly_canonical(path).u8string();
}

auto default_file_manager::absolute_path(const types::path &base_path, const types::path &path) const noexcept -> types::path
{
    return common::path::absolute_path(base_path, path).u8string();
}

auto default_file_manager::file_extension(const types::path &path) const noexcept -> std::u8string
{
    return std::filesystem::path{path}.extension().u8string();
}

} // namespace aeon::engine::core::hal

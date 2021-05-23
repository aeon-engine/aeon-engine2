// Distributed under the BSD 2-Clause License - Copyright 2019-2021 Robin Degen

#include "generic_image_codec.h"
#include <aeon/imaging/file/png_file.h>
#include <aeon/imaging/file/jpg_file.h>
#include <aeon/imaging/file/bmp_file.h>
#include <aeon/common/string.h>

namespace aeon::engine::import::codecs
{

generic_image_codec::generic_image_codec() = default;

generic_image_codec::~generic_image_codec() = default;

auto generic_image_codec::import_texture(const core::types::path &path) -> aeon::common::pmr::unique_ptr<resources::texture_data>
{
    const auto extension = core::hal::file_manager::get().file_extension(path);

    auto file = core::hal::file_manager::get().open_read(path);

    imaging::image img;

    if (aeon::common::string::iequals<char8_t>(extension, u8".png"))
    {
        img = imaging::file::png::load(*file);
    }
    else if (aeon::common::string::iequals<char8_t>(extension, u8".jpg") || aeon::common::string::iequals<char8_t>(extension, u8".jpeg"))
    {
        img = imaging::file::jpg::load(*file);
    }
    else if (aeon::common::string::iequals<char8_t>(extension, u8".bmp"))
    {
        img = imaging::file::bmp::load(*file);
    }
    else
    {
        // TODO
        throw std::runtime_error{"Unsupported image file format."};
    }

    // resources::texture_data{math::dimensions(img),
}

auto generic_image_codec::format_support_type(const std::u8string &extension) const noexcept -> format_type
{
    if (aeon::common::string::iequals<char8_t>(extension, u8".png") || aeon::common::string::iequals<char8_t>(extension, u8".jpg") || aeon::common::string::iequals<char8_t>(extension, u8".jpeg") ||
        aeon::common::string::iequals<char8_t>(extension, u8".bmp"))
    {
        return format_type::texture;
    }

    return format_type::unsupported;
}

} // namespace aeon::engine::import::codecs

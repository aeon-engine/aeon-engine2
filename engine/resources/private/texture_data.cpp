// Distributed under the BSD 2-Clause License - Copyright 2019-2021 Robin Degen

#include <aeon/engine/resources/texture_data.h>

namespace aeon::engine::resources
{

texture_data::texture_data(imaging::image image) noexcept
    : resource_data{}
    , image_{std::move(image)}
{
}

texture_data::texture_data(const resource_id id, imaging::image image) noexcept
    : resource_data{id}
    , image_{std::move(image)}
{
}

texture_data::~texture_data() = default;

auto texture_data::image() const noexcept -> const imaging::image &
{
    return image_;
}

auto texture_data::dependencies() const noexcept -> std::set<resource_id>
{
    return {};
}

} // namespace aeon::engine::resources

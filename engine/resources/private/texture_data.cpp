// Distributed under the BSD 2-Clause License - Copyright 2019-2021 Robin Degen

#include <aeon/engine/resources/texture_data.h>

namespace aeon::engine::resources
{

texture_data::texture_data(const math::size2d<std::uint32_t> dimensions, const common::format format, const std::uint32_t num_mips, std::vector<std::byte> data, std::pmr::memory_resource *allocator) noexcept
    : resource_data{allocator}
    , dimensions_{dimensions}
    , format_{format}
    , num_mips_{num_mips}
    , data_{std::move(data)}
{
}

texture_data::texture_data(const resource_id id, const math::size2d<std::uint32_t> dimensions, const common::format format, const std::uint32_t num_mips, std::vector<std::byte> data, std::pmr::memory_resource *allocator) noexcept
    : resource_data{id, allocator}
    , dimensions_{dimensions}
    , format_{format}
    , num_mips_{num_mips}
    , data_{std::move(data)}
{
}

texture_data::~texture_data() = default;

auto texture_data::dimensions() const noexcept -> math::size2d<std::uint32_t>
{
    return dimensions_;
}

auto texture_data::format() const noexcept -> common::format
{
    return format_;
}

auto texture_data::num_mips() const noexcept -> std::uint32_t
{
    return num_mips_;
}

auto texture_data::data() const noexcept -> const std::vector<std::byte> &
{
    return data_;
}

auto texture_data::dependencies() const noexcept -> std::pmr::set<resource_id>
{
    return {};
}

} // namespace aeon::engine::resources

// Distributed under the BSD 2-Clause License - Copyright 2019-2021 Robin Degen

#pragma once

#include <aeon/engine/resources/resource_data.h>
#include <aeon/engine/resources/export.h>
#include <aeon/engine/common/format.h>
#include <aeon/math/size2d.h>
#include <vector>

namespace aeon::engine::resources
{

class AEON_ENGINE_RESOURCES_EXPORT texture_data final : public resource_data
{
public:
    explicit texture_data(const math::size2d<std::uint32_t> dimensions, const common::format format, const std::uint32_t num_mips, std::vector<std::byte> data) noexcept;
    explicit texture_data(const resource_id id, math::size2d<std::uint32_t> dimensions, const common::format format, const std::uint32_t num_mips, std::vector<std::byte> data) noexcept;
    ~texture_data() final;

    texture_data(const texture_data &) = delete;
    auto operator=(const texture_data &) -> texture_data & = delete;

    texture_data(texture_data &&) noexcept = default;
    auto operator=(texture_data &&) noexcept -> texture_data & = default;

    [[nodiscard]] auto dimensions() const noexcept -> math::size2d<std::uint32_t>;
    [[nodiscard]] auto format() const noexcept -> common::format;
    [[nodiscard]] auto num_mips() const noexcept -> std::uint32_t;
    [[nodiscard]] auto data() const noexcept -> const std::vector<std::byte> &;

    [[nodiscard]] auto dependencies() const noexcept -> std::vector<resource_id> final;

private:
    math::size2d<std::uint32_t> dimensions_;
    common::format format_;
    std::uint32_t num_mips_;
    std::vector<std::byte> data_;
};

} // namespace aeon::engine::resources

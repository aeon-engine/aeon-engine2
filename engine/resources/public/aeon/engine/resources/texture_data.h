// Distributed under the BSD 2-Clause License - Copyright 2019-2021 Robin Degen

#pragma once

#include <aeon/engine/resources/resource_data.h>
#include <aeon/engine/resources/export.h>
#include <aeon/imaging/image.h>

namespace aeon::engine::resources
{

class AEON_ENGINE_RESOURCES_EXPORT texture_data final : public resource_data
{
public:
    explicit texture_data(imaging::image image) noexcept;
    explicit texture_data(const resource_id id, imaging::image image) noexcept;
    ~texture_data() final;

    texture_data(const texture_data &) = delete;
    auto operator=(const texture_data &) -> texture_data & = delete;

    texture_data(texture_data &&) noexcept = default;
    auto operator=(texture_data &&) noexcept -> texture_data & = default;

    [[nodiscard]] auto image() const noexcept -> const imaging::image &;
    [[nodiscard]] auto dependencies() const noexcept -> std::set<resource_id> final;

private:
    imaging::image image_;
};

} // namespace aeon::engine::resources

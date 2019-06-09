// Distributed under the BSD 2-Clause License - Copyright 2019-2021 Robin Degen

#pragma once

#include <aeon/rhi/resource.h>
#include <aeon/rhi/format.h>
#include <aeon/imaging/image_view.h>
#include <aeon/math/size2d.h>

namespace aeon::rhi
{

class texture : public resource
{
public:
    ~texture() override = default;

    texture(const texture &) = delete;
    auto operator=(const texture &) -> texture & = delete;

    texture(texture &&) noexcept = delete;
    auto operator=(texture &&) noexcept -> texture & = delete;

    [[nodiscard]] virtual auto get_texture1d() noexcept -> class texture1d *
    {
        return nullptr;
    }

    [[nodiscard]] virtual auto get_texture2d() noexcept -> class texture2d *
    {
        return nullptr;
    }

    [[nodiscard]] virtual auto get_texture3d() noexcept -> class texture3d *
    {
        return nullptr;
    }

    [[nodiscard]] auto mip_levels() const noexcept
    {
        return mip_levels_;
    }

    [[nodiscard]] auto format() const noexcept
    {
        return format_;
    }

protected:
    explicit texture(const std::uint32_t mip_levels, const aeon::rhi::format format) noexcept
        : resource{}
        , mip_levels_{mip_levels}
        , format_{format}
    {
    }

private:
    std::uint32_t mip_levels_;
    aeon::rhi::format format_;
};

class texture2d : public texture
{
public:
    ~texture2d() override = default;

    texture2d(const texture2d &) = delete;
    auto operator=(const texture2d &) -> texture2d & = delete;

    texture2d(texture2d &&) noexcept = delete;
    auto operator=(texture2d &&) noexcept -> texture2d & = delete;

    [[nodiscard]] auto get_texture2d() noexcept -> class texture2d * override
    {
        return this;
    }

    [[nodiscard]] auto size() const noexcept
    {
        return size_;
    }

protected:
    explicit texture2d(const math::size2d<imaging::image_view::dimensions_type> size, const std::uint32_t mip_levels, const aeon::rhi::format format) noexcept
        : texture{mip_levels, format}
        , size_{size}
    {
    }

private:
    math::size2d<imaging::image_view::dimensions_type> size_;
};

using texture2d_ref = common::intrusive_ptr<texture2d>;

} // namespace aeon::rhi

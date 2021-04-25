// Distributed under the BSD 2-Clause License - Copyright 2019-2021 Robin Degen

#pragma once

#include <cstdint>
#include <span>

namespace aeon::engine::rhi
{

class resource_data
{
public:
    explicit resource_data(const std::span<const void *> data) noexcept
        : data_{std::data(data)}
        , size_{std::size(data)}
    {
    }

    explicit resource_data(const void *data, const std::size_t size) noexcept
        : data_{data}
        , size_{size}
    {
    }

    ~resource_data() = default;

    resource_data(const resource_data &) noexcept = default;
    auto operator=(const resource_data &) noexcept -> resource_data & = default;

    resource_data(resource_data &&) noexcept = default;
    auto operator=(resource_data &&) noexcept -> resource_data & = default;

    [[nodiscard]] auto data() const noexcept
    {
        return data_;
    }

    [[nodiscard]] auto size() const noexcept
    {
        return static_cast<std::uint32_t>(size_);
    }

private:
    const void *data_;
    std::size_t size_;
};

class texture_resource_data : public resource_data
{
public:
    explicit texture_resource_data(const std::span<const void *> data, const std::uint32_t stride_y) noexcept
        : resource_data{data}
        , stride_y_{stride_y}
    {
    }

    explicit texture_resource_data(const void *data, const std::size_t size, const std::uint32_t stride_y) noexcept
        : resource_data{data, size}
        , stride_y_{stride_y}
    {
    }

    ~texture_resource_data() = default;

    texture_resource_data(const texture_resource_data &) noexcept = default;
    auto operator=(const texture_resource_data &) noexcept -> texture_resource_data & = default;

    texture_resource_data(texture_resource_data &&) noexcept = default;
    auto operator=(texture_resource_data &&) noexcept -> texture_resource_data & = default;

    [[nodiscard]] auto stride_y() const noexcept
    {
        return stride_y_;
    }

private:
    std::uint32_t stride_y_;
};

class texture3d_resource_data : public texture_resource_data
{
public:
    explicit texture3d_resource_data(const std::span<const void *> data, const std::uint32_t stride_y, const std::uint32_t slice_stride) noexcept
        : texture_resource_data{data, stride_y}
        , slice_stride_{slice_stride}
    {
    }

    explicit texture3d_resource_data(const void *data, const std::size_t size, const std::uint32_t stride_y, const std::uint32_t slice_stride) noexcept
        : texture_resource_data{data, size, stride_y}
        , slice_stride_{slice_stride}
    {
    }

    ~texture3d_resource_data() = default;

    texture3d_resource_data(const texture3d_resource_data &) noexcept = default;
    auto operator=(const texture3d_resource_data &) noexcept -> texture3d_resource_data & = default;

    texture3d_resource_data(texture3d_resource_data &&) noexcept = default;
    auto operator=(texture3d_resource_data &&) noexcept -> texture3d_resource_data & = default;

    [[nodiscard]] auto slice_stride() const noexcept
    {
        return slice_stride_;
    }

private:
    std::uint32_t slice_stride_;
};

} // namespace aeon::engine::rhi

// Distributed under the BSD 2-Clause License - Copyright 2019-2021 Robin Degen

#pragma once

#include <aeon/rhi/resource.h>
#include <aeon/common/flags.h>
#include <cstdint>

namespace aeon::rhi
{

enum class usage
{
    default_use,
    immutable,
    dynamic,
    staging,
};

enum class cpu_access : std::uint32_t
{
    none = 0,
    write = 0x10000L,
    read = 0x20000L
};

aeon_declare_flag_operators(cpu_access);

class buffer : public resource
{
public:
    ~buffer() override = default;

    buffer(const buffer &) = delete;
    auto operator=(const buffer &) -> buffer & = delete;

    buffer(buffer &&) noexcept = delete;
    auto operator=(buffer &&) noexcept -> buffer & = delete;

    [[nodiscard]] auto size() const noexcept
    {
        return size_;
    }

    [[nodiscard]] auto usage() const noexcept
    {
        return usage_;
    }

protected:
    explicit buffer(const std::uint32_t size, const aeon::rhi::usage usage) noexcept
        : size_{size}
        , usage_{usage}
    {
    }

private:
    std::uint32_t size_;
    aeon::rhi::usage usage_;
};

class index_buffer : public buffer
{
public:
    ~index_buffer() override = default;

    index_buffer(const index_buffer &) = delete;
    auto operator=(const index_buffer &) -> index_buffer & = delete;

    index_buffer(index_buffer &&) noexcept = delete;
    auto operator=(index_buffer &&) noexcept -> index_buffer & = delete;

protected:
    explicit index_buffer(const std::uint32_t size, const aeon::rhi::usage usage) noexcept
        : buffer{size, usage}
    {
    }
};

using index_buffer_ref = common::intrusive_ptr<index_buffer>;

class vertex_buffer : public buffer
{
public:
    ~vertex_buffer() override = default;

    vertex_buffer(const vertex_buffer &) = delete;
    auto operator=(const vertex_buffer &) -> vertex_buffer & = delete;

    vertex_buffer(vertex_buffer &&) noexcept = delete;
    auto operator=(vertex_buffer &&) noexcept -> vertex_buffer & = delete;

protected:
    explicit vertex_buffer(const std::uint32_t size, const aeon::rhi::usage usage) noexcept
        : buffer{size, usage}
    {
    }
};

using vertex_buffer_ref = common::intrusive_ptr<vertex_buffer>;

class constant_buffer : public buffer
{
public:
    ~constant_buffer() override = default;

    constant_buffer(const constant_buffer &) = delete;
    auto operator=(const constant_buffer &) -> constant_buffer & = delete;

    constant_buffer(constant_buffer &&) noexcept = delete;
    auto operator=(constant_buffer &&) noexcept -> constant_buffer & = delete;

protected:
    explicit constant_buffer(const std::uint32_t size, const aeon::rhi::usage usage) noexcept
        : buffer{size, usage}
    {
    }
};

using constant_buffer_ref = common::intrusive_ptr<constant_buffer>;

} // namespace aeon::rhi

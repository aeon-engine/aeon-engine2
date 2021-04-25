// Distributed under the BSD 2-Clause License - Copyright 2019-2021 Robin Degen

#pragma once

#include <aeon/engine/rhi/resource.h>
#include <aeon/common/intrusive_ptr.h>
#include <cstddef>
#include <cstdint>

namespace aeon::engine::rhi
{

enum class shader_frequency : std::uint8_t
{
    vertex,
    hull,
    domain,
    pixel,
    geometry,
    compute,

    total_count
};

static constexpr auto total_shader_frequencies = static_cast<int>(shader_frequency::total_count);

class shader : public resource
{
public:
    explicit shader(const shader_frequency frequency) noexcept
        : hash_{}
        , frequency_{frequency}
    {
    }

    ~shader() override = default;

    shader(const shader &) = delete;
    auto operator=(const shader &) -> shader & = delete;

    shader(shader &&) noexcept = delete;
    auto operator=(shader &&) noexcept -> shader & = delete;

    [[nodiscard]] auto hash() const noexcept
    {
        return hash_;
    }

    void hash(const std::size_t &h) noexcept
    {
        hash_ = h;
    }

    [[nodiscard]] auto frequency() const noexcept
    {
        return frequency_;
    }

private:
    std::size_t hash_;
    shader_frequency frequency_;
};

class graphics_shader : public shader
{
public:
    graphics_shader(const shader_frequency frequency) noexcept
        : shader{frequency}
    {
    }

    ~graphics_shader() override = default;

    graphics_shader(const graphics_shader &) = delete;
    auto operator=(const graphics_shader &) -> graphics_shader & = delete;

    graphics_shader(graphics_shader &&) noexcept = delete;
    auto operator=(graphics_shader &&) noexcept -> graphics_shader & = delete;

    [[nodiscard]] virtual auto get_vertex_shader() noexcept -> class vertex_shader *
    {
        return nullptr;
    }

    [[nodiscard]] virtual auto get_pixel_shader() noexcept -> class pixel_shader *
    {
        return nullptr;
    }
};

class vertex_shader : public graphics_shader
{
public:
    vertex_shader() noexcept
        : graphics_shader{shader_frequency::vertex}
    {
    }

    ~vertex_shader() override = default;

    vertex_shader(const vertex_shader &) = delete;
    auto operator=(const vertex_shader &) -> vertex_shader & = delete;

    vertex_shader(vertex_shader &&) noexcept = delete;
    auto operator=(vertex_shader &&) noexcept -> vertex_shader & = delete;

    [[nodiscard]] auto get_vertex_shader() noexcept -> class vertex_shader * final
    {
        return this;
    }
};

using vertex_shader_ref = aeon::common::intrusive_ptr<vertex_shader>;

class pixel_shader : public graphics_shader
{
public:
    pixel_shader() noexcept
        : graphics_shader{shader_frequency::pixel}
    {
    }

    ~pixel_shader() override = default;

    pixel_shader(const pixel_shader &) = delete;
    auto operator=(const pixel_shader &) -> pixel_shader & = delete;

    pixel_shader(pixel_shader &&) noexcept = delete;
    auto operator=(pixel_shader &&) noexcept -> pixel_shader & = delete;

    [[nodiscard]] auto get_pixel_shader() noexcept -> class pixel_shader * final
    {
        return this;
    }
};

using pixel_shader_ref = aeon::common::intrusive_ptr<pixel_shader>;

} // namespace aeon::engine::rhi

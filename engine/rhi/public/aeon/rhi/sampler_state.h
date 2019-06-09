// Distributed under the BSD 2-Clause License - Copyright 2019-2021 Robin Degen

#pragma once

#include <aeon/rhi/resource.h>
#include <aeon/rhi/filter_type.h>
#include <aeon/rhi/wrap_mode.h>

namespace aeon::rhi
{

class sampler_state_settings
{
public:
    explicit sampler_state_settings(const filter_type filter, const wrap_mode wrap_mode = wrap_mode::wrap, const std::uint32_t max_anisotropy = 1.0f) noexcept
        : sampler_state_settings{filter, wrap_mode, wrap_mode, wrap_mode, 0.0f, max_anisotropy, 0.0f, 1000.0f}
    {
    }

    explicit sampler_state_settings(const filter_type filter, const wrap_mode wrap_mode_u, const wrap_mode wrap_mode_v, const wrap_mode wrap_mode_w, const float mip_lod_bias,
                                    const std::uint32_t max_anisotropy, const float min_lod, const float max_lod) noexcept
        : filter_{filter}
        , wrap_mode_u_{wrap_mode_u}
        , wrap_mode_v_{wrap_mode_v}
        , wrap_mode_w_{wrap_mode_w}
        , mip_lod_bias_{mip_lod_bias}
        , max_anisotropy_{max_anisotropy}
        , min_lod_{min_lod}
        , max_lod_{max_lod}
    {
    }

    virtual ~sampler_state_settings() = default;

    sampler_state_settings(const sampler_state_settings &) noexcept = default;
    auto operator=(const sampler_state_settings &) noexcept -> sampler_state_settings & = default;

    sampler_state_settings(sampler_state_settings &&) noexcept = delete;
    auto operator=(sampler_state_settings &&) noexcept -> sampler_state_settings & = delete;

    [[nodiscard]] auto filter() const noexcept
    {
        return filter_;
    }

    [[nodiscard]] auto wrap_mode_u() const noexcept
    {
        return wrap_mode_u_;
    }

    [[nodiscard]] auto wrap_mode_v() const noexcept
    {
        return wrap_mode_v_;
    }

    [[nodiscard]] auto wrap_mode_w() const noexcept
    {
        return wrap_mode_w_;
    }

    [[nodiscard]] auto mip_lod_bias() const noexcept
    {
        return mip_lod_bias_;
    }

    [[nodiscard]] auto max_anisotropy() const noexcept
    {
        return max_anisotropy_;
    }

    [[nodiscard]] auto min_lod() const noexcept
    {
        return min_lod_;
    }

    [[nodiscard]] auto max_lod() const noexcept
    {
        return max_lod_;
    }

private:
    filter_type filter_;
    wrap_mode wrap_mode_u_;
    wrap_mode wrap_mode_v_;
    wrap_mode wrap_mode_w_;
    float mip_lod_bias_;
    std::uint32_t max_anisotropy_;
    float min_lod_;
    float max_lod_;
};

class sampler_state : public sampler_state_settings, public resource
{
public:
    ~sampler_state() override = default;

    sampler_state(const sampler_state &) = delete;
    auto operator=(const sampler_state &) -> sampler_state & = delete;

    sampler_state(sampler_state &&) noexcept = delete;
    auto operator=(sampler_state &&) noexcept -> sampler_state & = delete;

protected:
    explicit sampler_state(const sampler_state_settings &settings) noexcept
        : sampler_state_settings{settings}
        , resource{}
    {
    }
};

using sampler_state_ref = common::intrusive_ptr<sampler_state>;

} // namespace aeon::rhi

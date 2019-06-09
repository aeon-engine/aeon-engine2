// Distributed under the BSD 2-Clause License - Copyright 2019-2021 Robin Degen

#pragma once

#include <aeon/rhi/texture.h>
#include <wrl/client.h>
#include <d3d11.h>

namespace aeon::rhi::dx11
{

template <typename BaseT>
class dx11_rhi_texture_base : public BaseT
{
public:
    template <typename... args_t>
    explicit dx11_rhi_texture_base(ID3D11Resource *texture, args_t &&...args) noexcept
        : BaseT{std::forward<args_t>(args)...}
        , texture{texture}
    {
    }

    ~dx11_rhi_texture_base() override = default;

    dx11_rhi_texture_base(const dx11_rhi_texture_base &) = delete;
    auto operator=(const dx11_rhi_texture_base &) -> dx11_rhi_texture_base & = delete;

    dx11_rhi_texture_base(dx11_rhi_texture_base &&) noexcept = delete;
    auto operator=(dx11_rhi_texture_base &&) noexcept -> dx11_rhi_texture_base & = delete;

    Microsoft::WRL::ComPtr<ID3D11Resource> texture;

private:
    [[nodiscard]] auto native_impl_internal() noexcept -> void * final
    {
        return this;
    }
};

class dx11_rhi_texture2d final : public dx11_rhi_texture_base<texture2d>
{
public:
    explicit dx11_rhi_texture2d(ID3D11Resource *texture, const math::size2d<imaging::image_view::dimensions_type> size, const std::uint32_t mip_levels, const rhi::format format) noexcept
        : dx11_rhi_texture_base<texture2d>{texture, size, mip_levels, format}
    {
    }

    ~dx11_rhi_texture2d() final = default;

    dx11_rhi_texture2d(const dx11_rhi_texture2d &) = delete;
    auto operator=(const dx11_rhi_texture2d &) -> dx11_rhi_texture2d & = delete;

    dx11_rhi_texture2d(dx11_rhi_texture2d &&) noexcept = delete;
    auto operator=(dx11_rhi_texture2d &&) noexcept -> dx11_rhi_texture2d & = delete;

private:
};

} // namespace aeon::rhi::dx11

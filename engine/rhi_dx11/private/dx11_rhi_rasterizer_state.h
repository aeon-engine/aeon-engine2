// Distributed under the BSD 2-Clause License - Copyright 2019-2021 Robin Degen

#pragma once

#include <aeon/rhi/rasterizer_state.h>
#include <d3d11.h>
#include <wrl/client.h>

namespace aeon::rhi::dx11
{

class dx11_rhi_rasterizer_state : public rasterizer_state
{
public:
    explicit dx11_rhi_rasterizer_state(ID3D11RasterizerState *state) noexcept
        : rasterizer_state{}
        , state{state}
    {
    }

    ~dx11_rhi_rasterizer_state() = default;

    dx11_rhi_rasterizer_state(const dx11_rhi_rasterizer_state &) = delete;
    auto operator=(const dx11_rhi_rasterizer_state &) -> dx11_rhi_rasterizer_state & = delete;

    dx11_rhi_rasterizer_state(dx11_rhi_rasterizer_state &&) noexcept = delete;
    auto operator=(dx11_rhi_rasterizer_state &&) noexcept -> dx11_rhi_rasterizer_state & = delete;

    Microsoft::WRL::ComPtr<ID3D11RasterizerState> state;

private:
    [[nodiscard]] auto native_impl_internal() noexcept -> void * final
    {
        return this;
    }
};

} // namespace aeon::rhi::opengl

// Distributed under the BSD 2-Clause License - Copyright 2019-2021 Robin Degen

#pragma once

#include <aeon/engine/rhi/depth_stencil_state.h>
#include <d3d11.h>
#include <wrl/client.h>

namespace aeon::engine::rhi::dx11
{

class dx11_rhi_depth_stencil_state final : public depth_stencil_state
{
public:
    explicit dx11_rhi_depth_stencil_state(ID3D11DepthStencilState *state) noexcept
        : state{state}
    {
    }

    ~dx11_rhi_depth_stencil_state() final = default;

    dx11_rhi_depth_stencil_state(const dx11_rhi_depth_stencil_state &) = delete;
    auto operator=(const dx11_rhi_depth_stencil_state &) -> dx11_rhi_depth_stencil_state & = delete;

    dx11_rhi_depth_stencil_state(dx11_rhi_depth_stencil_state &&) noexcept = delete;
    auto operator=(dx11_rhi_depth_stencil_state &&) noexcept -> dx11_rhi_depth_stencil_state & = delete;

    Microsoft::WRL::ComPtr<ID3D11DepthStencilState> state;

private:
    [[nodiscard]] auto native_impl_internal() noexcept -> void * final
    {
        return this;
    }
};

} // namespace aeon::engine::rhi::dx11

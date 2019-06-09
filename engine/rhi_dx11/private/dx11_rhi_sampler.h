// Distributed under the BSD 2-Clause License - Copyright 2019-2021 Robin Degen

#pragma once

#include <aeon/rhi/sampler_state.h>
#include <d3d11.h>
#include <wrl/client.h>

namespace aeon::rhi::dx11
{

class dx11_rhi_sampler_state final : public sampler_state
{
public:
    explicit dx11_rhi_sampler_state(const sampler_state_settings &settings, ID3D11SamplerState *state) noexcept
        : sampler_state{settings}
        , state{state}
    {
    }

    ~dx11_rhi_sampler_state() final = default;

    dx11_rhi_sampler_state(const dx11_rhi_sampler_state &) = delete;
    auto operator=(const dx11_rhi_sampler_state &) -> dx11_rhi_sampler_state & = delete;

    dx11_rhi_sampler_state(dx11_rhi_sampler_state &&) noexcept = delete;
    auto operator=(dx11_rhi_sampler_state &&) noexcept -> dx11_rhi_sampler_state & = delete;

    Microsoft::WRL::ComPtr<ID3D11SamplerState> state;

private:
    [[nodiscard]] auto native_impl_internal() noexcept -> void * final
    {
        return this;
    }
};

} // namespace aeon::rhi::dx11

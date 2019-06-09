// Distributed under the BSD 2-Clause License - Copyright 2019-2021 Robin Degen

#pragma once

#include <aeon/rhi/bound_shader_state.h>
#include <d3d11.h>
#include <wrl/client.h>

namespace aeon::rhi::dx11
{

class dx11_rhi_bound_shader_state : public bound_shader_state
{
public:
    explicit dx11_rhi_bound_shader_state(ID3D11InputLayout *input_layout, rhi::vertex_shader *vertex_shader, rhi::pixel_shader *pixel_shader)
        : bound_shader_state{vertex_shader, pixel_shader}
        , input_layout{input_layout}
    {
    }

    ~dx11_rhi_bound_shader_state() final = default;

    dx11_rhi_bound_shader_state(const dx11_rhi_bound_shader_state &) = delete;
    auto operator=(const dx11_rhi_bound_shader_state &) -> dx11_rhi_bound_shader_state & = delete;

    dx11_rhi_bound_shader_state(dx11_rhi_bound_shader_state &&) noexcept = delete;
    auto operator=(dx11_rhi_bound_shader_state &&) noexcept -> dx11_rhi_bound_shader_state & = delete;

    Microsoft::WRL::ComPtr<ID3D11InputLayout> input_layout;

private:
    [[nodiscard]] auto native_impl_internal() noexcept -> void * final
    {
        return this;
    }
};

} // namespace aeon::rhi::dx11

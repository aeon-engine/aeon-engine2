// Distributed under the BSD 2-Clause License - Copyright 2019-2021 Robin Degen

#pragma once

#include <aeon/rhi/shader_resource_view.h>
#include <wrl/client.h>
#include <d3d11.h>

namespace aeon::rhi::dx11
{

class dx11_rhi_shader_resource_view final : public shader_resource_view
{
public:
    explicit dx11_rhi_shader_resource_view(ID3D11ShaderResourceView *resource_view)
        : shader_resource_view{}
        , resource_view{resource_view}
    {
    }

    ~dx11_rhi_shader_resource_view() final = default;

    dx11_rhi_shader_resource_view(const dx11_rhi_shader_resource_view &) = delete;
    auto operator=(const dx11_rhi_shader_resource_view &) -> dx11_rhi_shader_resource_view & = delete;

    dx11_rhi_shader_resource_view(dx11_rhi_shader_resource_view &&) noexcept = delete;
    auto operator=(dx11_rhi_shader_resource_view &&) noexcept -> dx11_rhi_shader_resource_view & = delete;

    Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> resource_view;

private:
    [[nodiscard]] auto native_impl_internal() noexcept -> void * final
    {
        return this;
    }
};

} // namespace aeon::rhi::dx11

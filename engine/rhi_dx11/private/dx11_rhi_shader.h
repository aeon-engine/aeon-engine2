// Distributed under the BSD 2-Clause License - Copyright 2019-2021 Robin Degen

#pragma once

#include <aeon/engine/rhi/shader.h>
#include <d3d11.h>
#include <wrl/client.h>
#include <span>

namespace aeon::engine::rhi::dx11
{

template <typename dx_type, typename rhi_type>
class dx11_rhi_shader_base final : public rhi_type
{
public:
    explicit dx11_rhi_shader_base(dx_type *shader, const std::span<const std::byte> &data) noexcept
        : rhi_type{}
        , shader{shader}
        , compiled_shader(std::size(data))
    {
        std::copy_n(std::begin(data), std::size(data), std::begin(compiled_shader));
    }

    ~dx11_rhi_shader_base() final = default;

    dx11_rhi_shader_base(const dx11_rhi_shader_base &) = delete;
    auto operator=(const dx11_rhi_shader_base &) -> dx11_rhi_shader_base & = delete;

    dx11_rhi_shader_base(dx11_rhi_shader_base &&) noexcept = delete;
    auto operator=(dx11_rhi_shader_base &&) noexcept -> dx11_rhi_shader_base & = delete;

    Microsoft::WRL::ComPtr<dx_type> shader;
    std::vector<std::byte> compiled_shader;

private:
    [[nodiscard]] auto native_impl_internal() noexcept -> void * final
    {
        return this;
    }
};

using dx11_rhi_vertex_shader = dx11_rhi_shader_base<ID3D11VertexShader, vertex_shader>;
using dx11_rhi_pixel_shader = dx11_rhi_shader_base<ID3D11PixelShader, pixel_shader>;

} // namespace aeon::engine::rhi::dx11

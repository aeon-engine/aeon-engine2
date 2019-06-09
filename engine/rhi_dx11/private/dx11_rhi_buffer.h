// Distributed under the BSD 2-Clause License - Copyright 2019-2021 Robin Degen

#pragma once

#include <aeon/rhi/buffer.h>
#include <d3d11.h>
#include <wrl/client.h>

namespace aeon::rhi::dx11
{

template <typename BaseT>
class dx11_rhi_buffer_base : public BaseT
{
public:
    template <typename... args_t>
    explicit dx11_rhi_buffer_base(ID3D11Buffer *buffer, args_t &&...args) noexcept
        : BaseT{std::forward<args_t>(args)...}
        , buffer{buffer}
    {
    }

    ~dx11_rhi_buffer_base() override = default;

    dx11_rhi_buffer_base(const dx11_rhi_buffer_base &) = delete;
    auto operator=(const dx11_rhi_buffer_base &) -> dx11_rhi_buffer_base & = delete;

    dx11_rhi_buffer_base(dx11_rhi_buffer_base &&) noexcept = delete;
    auto operator=(dx11_rhi_buffer_base &&) noexcept -> dx11_rhi_buffer_base & = delete;

    Microsoft::WRL::ComPtr<ID3D11Buffer> buffer;
};

class dx11_rhi_vertex_buffer final : public dx11_rhi_buffer_base<vertex_buffer>
{
public:
    explicit dx11_rhi_vertex_buffer(ID3D11Buffer *buffer, const std::uint32_t size, const rhi::usage usage) noexcept
        : dx11_rhi_buffer_base<vertex_buffer>{buffer, size, usage}
    {
    }

    ~dx11_rhi_vertex_buffer() final = default;

    dx11_rhi_vertex_buffer(const dx11_rhi_vertex_buffer &) = delete;
    auto operator=(const dx11_rhi_vertex_buffer &) -> dx11_rhi_vertex_buffer & = delete;

    dx11_rhi_vertex_buffer(dx11_rhi_vertex_buffer &&) noexcept = delete;
    auto operator=(dx11_rhi_vertex_buffer &&) noexcept -> dx11_rhi_vertex_buffer & = delete;

private:
    [[nodiscard]] auto native_impl_internal() noexcept -> void * final
    {
        return this;
    }
};

class dx11_rhi_index_buffer final : public dx11_rhi_buffer_base<index_buffer>
{
public:
    explicit dx11_rhi_index_buffer(ID3D11Buffer *buffer, const std::uint32_t size, const rhi::usage usage) noexcept
        : dx11_rhi_buffer_base<index_buffer>{buffer, size, usage}
    {
    }

    ~dx11_rhi_index_buffer() final = default;

    dx11_rhi_index_buffer(const dx11_rhi_index_buffer &) = delete;
    auto operator=(const dx11_rhi_index_buffer &) -> dx11_rhi_index_buffer & = delete;

    dx11_rhi_index_buffer(dx11_rhi_index_buffer &&) noexcept = delete;
    auto operator=(dx11_rhi_index_buffer &&) noexcept -> dx11_rhi_index_buffer & = delete;

private:
    [[nodiscard]] auto native_impl_internal() noexcept -> void * final
    {
        return this;
    }
};

class dx11_rhi_constant_buffer final : public dx11_rhi_buffer_base<constant_buffer>
{
public:
    explicit dx11_rhi_constant_buffer(ID3D11Buffer *buffer, const std::uint32_t size, const rhi::usage usage) noexcept
        : dx11_rhi_buffer_base<constant_buffer>{buffer, size, usage}
    {
    }

    ~dx11_rhi_constant_buffer() final = default;

    dx11_rhi_constant_buffer(const dx11_rhi_constant_buffer &) = delete;
    auto operator=(const dx11_rhi_constant_buffer &) -> dx11_rhi_constant_buffer & = delete;

    dx11_rhi_constant_buffer(dx11_rhi_constant_buffer &&) noexcept = delete;
    auto operator=(dx11_rhi_constant_buffer &&) noexcept -> dx11_rhi_constant_buffer & = delete;

private:
    [[nodiscard]] auto native_impl_internal() noexcept -> void * final
    {
        return this;
    }
};

} // namespace aeon::rhi::dx11

// Distributed under the BSD 2-Clause License - Copyright 2019-2021 Robin Degen

#pragma once

#include "dx11_context.h"
#include <stdexcept>
#include <system_error>

namespace aeon::engine::rhi::dx11
{

class checked_hresult final
{
public:
#if (defined(AEON_RHI_DX11_ENABLE_ERROR_CHECKING))
    static constexpr auto error_check_enabled = true;
#else
    static constexpr auto error_check_enabled = false;
#endif

    explicit checked_hresult(const HRESULT result) noexcept(!error_check_enabled)
    {
#if (defined(AEON_RHI_DX11_ENABLE_ERROR_CHECKING))
        if (FAILED(result))
        {
            const auto message = std::system_category().message(result);
            throw std::runtime_error{std::string{"DirectX11 call failed: "} + message};
        }
#endif
    }

    ~checked_hresult() = default;

    checked_hresult(const checked_hresult &) noexcept = delete;
    auto operator=(const checked_hresult &) noexcept -> checked_hresult & = delete;

    checked_hresult(checked_hresult &&) noexcept = delete;
    auto operator=(checked_hresult &&) noexcept -> checked_hresult & = delete;
};

} // namespace aeon::engine::rhi::dx11

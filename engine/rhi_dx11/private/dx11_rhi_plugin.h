// Distributed under the BSD 2-Clause License - Copyright 2019-2021 Robin Degen

#pragma once

#include <aeon/engine/rhi/rhi_plugin.h>
#include "dx11_device.h"
#include <memory>

namespace aeon::engine::rhi::dx11
{

class dx11_rhi_plugin final : public rhi_plugin
{
public:
    dx11_rhi_plugin();
    ~dx11_rhi_plugin() override;

    dx11_rhi_plugin(const dx11_rhi_plugin &) = delete;
    auto operator=(const dx11_rhi_plugin &) -> dx11_rhi_plugin & = delete;

    dx11_rhi_plugin(dx11_rhi_plugin &&) noexcept = delete;
    auto operator=(dx11_rhi_plugin &&) noexcept -> dx11_rhi_plugin & = delete;

    [[nodiscard]] auto plugin_name() const noexcept -> const char * override;
    [[nodiscard]] auto plugin_version_string() const noexcept -> const char * override;

    [[nodiscard]] auto get_rhi_device() const noexcept -> device * override;

private:
    std::unique_ptr<dx11_device> device_;
};

} // namespace aeon::engine::rhi::dx11

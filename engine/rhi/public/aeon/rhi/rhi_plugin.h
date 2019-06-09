// Distributed under the BSD 2-Clause License - Copyright 2019-2021 Robin Degen

#pragma once

#include <aeon/plugins/plugin.h>

namespace aeon::rhi
{

class device;

class rhi_plugin : public plugins::plugin
{
public:
    ~rhi_plugin() override = default;

    rhi_plugin(const rhi_plugin &) = delete;
    auto operator=(const rhi_plugin &) -> rhi_plugin & = delete;

    rhi_plugin(rhi_plugin &&) noexcept = delete;
    auto operator=(rhi_plugin &&) noexcept -> rhi_plugin & = delete;

    [[nodiscard]] virtual auto get_rhi_device() const noexcept -> device * = 0;

protected:
    rhi_plugin() = default;
};

} // namespace aeon::rhi

// Distributed under the BSD 2-Clause License - Copyright 2019-2021 Robin Degen

#pragma once

#include <aeon/engine/rhi/rhi_plugin.h>
#include <aeon/rhi/export.h>
#include <aeon/plugins/plugin_loader.h>

namespace aeon::engine::rhi
{

class AEON_ENGINE_RHI_EXPORT rhi
{
public:
    [[nodiscard]] static auto get() -> rhi &;

    ~rhi();

    rhi(const rhi &) = delete;
    auto operator=(const rhi &) -> rhi & = delete;

    rhi(rhi &&) noexcept = delete;
    auto operator=(rhi &&) noexcept -> rhi & = delete;

    [[nodiscard]] auto get_rhi_device() const noexcept -> device &
    {
        return *device_;
    }

private:
    rhi();

    void load_rhi_plugin();

    plugins::plugin_loader loader_;
    plugins::scoped_plugin<rhi_plugin> plugin_;

    device *device_;
};

} // namespace aeon::engine::rhi

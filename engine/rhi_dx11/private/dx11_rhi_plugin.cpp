#include "dx11_rhi_plugin.h"

namespace aeon::rhi::dx11
{

dx11_rhi_plugin::dx11_rhi_plugin()
    : device_{std::make_unique<dx11_device>()}
{
}

dx11_rhi_plugin::~dx11_rhi_plugin() = default;

auto dx11_rhi_plugin::plugin_name() const noexcept -> const char *
{
    return "DirectX11 RHI Plugin";
}

auto dx11_rhi_plugin::plugin_version_string() const noexcept -> const char *
{
    return "1.0";
}

auto dx11_rhi_plugin::get_rhi_device() const noexcept -> device *
{
    return device_.get();
}

} // namespace aeon::rhi::dx11

aeon_register_plugin(aeon::rhi::dx11::dx11_rhi_plugin)

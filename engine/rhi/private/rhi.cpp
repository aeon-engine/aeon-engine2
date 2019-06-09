#include <aeon/rhi/rhi.h>

namespace aeon::rhi
{

auto rhi::get() -> rhi &
{
    static rhi instance;
    return instance;
}

rhi::~rhi() = default;

rhi::rhi()
    : loader_{}
    , device_{}
{
    load_rhi_plugin();
}

void rhi::load_rhi_plugin()
{
#ifdef _DEBUG
#define DEBUG_POSTFIX "_d"
#else
#define DEBUG_POSTFIX
#endif

    plugin_ = loader_.load<rhi_plugin>("aeon_engine_rhi_dx11" DEBUG_POSTFIX);
    device_ = plugin_->get_rhi_device();
}

} // namespace aeon::rhi

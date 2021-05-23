// Distributed under the BSD 2-Clause License - Copyright 2019-2021 Robin Degen

#include "default_file_manager.h"

namespace aeon::engine::core::hal
{

[[nodiscard]] AEON_ENGINE_CORE_EXPORT auto file_manager::get() noexcept -> file_manager &
{
    // Currently there's only one type of file manager. If a certain platform requires another one, add some logic here to create the correct one.
    static default_file_manager mgr;
    return mgr;
}

} // namespace aeon::engine::core::hal

// Distributed under the BSD 2-Clause License - Copyright 2019-2021 Robin Degen

#include <aeon/engine/resources/resource_data.h>

namespace aeon::engine::resources
{

resource_data::resource_data() noexcept
    : id_{resource_id::generate()}
{
}

resource_data::resource_data(const resource_id &id)
    : id_{id}
{
}

resource_data::~resource_data() = default;

auto resource_data::id() const noexcept -> const resource_id &
{
    return id_;
}

} // namespace aeon::engine::resources

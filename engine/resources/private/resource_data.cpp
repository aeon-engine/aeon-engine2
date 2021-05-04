// Distributed under the BSD 2-Clause License - Copyright 2019-2021 Robin Degen

#include <aeon/engine/resources/resource_data.h>

namespace aeon::engine::resources
{

resource_data::resource_data(std::pmr::memory_resource *allocator) noexcept
    : allocator_{allocator}
    , id_{resource_id::generate()}
{
}

resource_data::resource_data(const resource_id &id, std::pmr::memory_resource *allocator)
    : allocator_{allocator}
    , id_{id}
{
}

resource_data::~resource_data() = default;

auto resource_data::id() const noexcept -> const resource_id &
{
    return id_;
}

auto resource_data::get_allocator() const noexcept -> std::pmr::memory_resource *
{
    return allocator_;
}

} // namespace aeon::engine::resources

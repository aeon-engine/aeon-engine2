// Distributed under the BSD 2-Clause License - Copyright 2019-2021 Robin Degen

#pragma once

#include <aeon/engine/rhi/resource.h>

namespace aeon::engine::rhi
{

class shader_resource_view : public resource
{
public:
    ~shader_resource_view() override = default;

    shader_resource_view(const shader_resource_view &) = delete;
    auto operator=(const shader_resource_view &) -> shader_resource_view & = delete;

    shader_resource_view(shader_resource_view &&) noexcept = delete;
    auto operator=(shader_resource_view &&) noexcept -> shader_resource_view & = delete;

protected:
    explicit shader_resource_view() noexcept = default;
};

using shader_resource_view_ref = aeon::common::intrusive_ptr<shader_resource_view>;

} // namespace aeon::engine::rhi

// Distributed under the BSD 2-Clause License - Copyright 2019-2021 Robin Degen

#pragma once

#include <aeon/engine/rhi/resource.h>
#include <aeon/engine/rhi/shader.h>

namespace aeon::engine::rhi
{

class bound_shader_state : public resource
{
public:
    ~bound_shader_state() override = default;

    bound_shader_state(const bound_shader_state &) = delete;
    auto operator=(const bound_shader_state &) -> bound_shader_state & = delete;

    bound_shader_state(bound_shader_state &&) noexcept = delete;
    auto operator=(bound_shader_state &&) noexcept -> bound_shader_state & = delete;

    [[nodiscard]] auto has_vertex_shader() const noexcept
    {
        return vertex_shader_.get() != nullptr;
    }

    [[nodiscard]] auto vertex_shader() const noexcept
    {
        return vertex_shader_.get();
    }

    [[nodiscard]] auto has_pixel_shader() const noexcept
    {
        return pixel_shader_.get() != nullptr;
    }

    [[nodiscard]] auto pixel_shader() const noexcept
    {
        return pixel_shader_.get();
    }

protected:
    explicit bound_shader_state(engine::rhi::vertex_shader *vertex_shader, engine::rhi::pixel_shader *pixel_shader) noexcept
        : resource{}
        , vertex_shader_{vertex_shader}
        , pixel_shader_{pixel_shader}
    {
    }

private:
    vertex_shader_ref vertex_shader_;
    pixel_shader_ref pixel_shader_;
};

using bound_shader_state_ref = aeon::common::intrusive_ptr<bound_shader_state>;

} // namespace aeon::engine::rhi

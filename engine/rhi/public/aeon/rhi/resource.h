// Distributed under the BSD 2-Clause License - Copyright 2019-2021 Robin Degen

#pragma once

#include <aeon/common/intrusive_ptr.h>
#include <cstdint>
#include <atomic>

namespace aeon::rhi
{

class resource
{
public:
    virtual ~resource() = default;

    resource(const resource &) = delete;
    auto operator=(const resource &) -> resource & = delete;

    resource(resource &&) noexcept = delete;
    auto operator=(resource &&) noexcept -> resource & = delete;

    void intrusive_ptr_add_ref() noexcept
    {
        ++ref_count_;
    }

    void intrusive_ptr_release() noexcept
    {
        --ref_count_;

        if (ref_count_ <= 0)
            std::default_delete<resource>{}(this);
    }

    template <typename T>
    [[nodiscard]] auto native_impl() noexcept
    {
        return static_cast<T *>(native_impl_internal());
    }

protected:
    resource() noexcept
        : ref_count_{0}
    {
    }

    [[nodiscard]] virtual auto native_impl_internal() noexcept -> void * = 0;

private:
    std::atomic<std::int32_t> ref_count_;
};

} // namespace aeon::rhi

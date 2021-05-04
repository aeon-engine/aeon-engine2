// Distributed under the BSD 2-Clause License - Copyright 2019-2021 Robin Degen

#pragma once

#include "codecs/codec.h"
#include <aeon/engine/import/importer.h>
#include <aeon/common/pmr.h>
#include <vector>

namespace aeon::engine::import
{

class importer_impl final : public importer
{
public:
    explicit importer_impl(std::pmr::memory_resource *allocator = std::pmr::get_default_resource()) noexcept;
    ~importer_impl() final;

    importer_impl(const importer_impl &) = delete;
    auto operator=(const importer_impl &) -> importer_impl & = delete;

    importer_impl(importer_impl &&) noexcept = delete;
    auto operator=(importer_impl &&) noexcept -> importer_impl & = delete;

    [[nodiscard]] auto import(const std::filesystem::path &path, std::pmr::memory_resource *allocator = std::pmr::get_default_resource()) -> import_result final;

private:
    std::pmr::vector<std::unique_ptr<codecs::codec>> codecs_;
};

} // namespace aeon::engine::import

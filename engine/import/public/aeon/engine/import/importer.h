// Distributed under the BSD 2-Clause License - Copyright 2019-2021 Robin Degen

#pragma once

#include <aeon/engine/import/import_result.h>
#include <aeon/engine/import/export.h>
#include <memory_resource>
#include <filesystem>

namespace aeon::engine::import
{

class importer
{
public:
    AEON_ENGINE_IMPORT_EXPORT [[nodiscard]] static auto create(std::pmr::memory_resource *allocator = std::pmr::get_default_resource()) -> std::unique_ptr<importer>;

    virtual ~importer() = default;

    importer(const importer &) = delete;
    auto operator=(const importer &) -> importer & = delete;

    importer(importer &&) noexcept = delete;
    auto operator=(importer &&) noexcept -> importer & = delete;

    [[nodiscard]] virtual auto import(const std::filesystem::path &path, std::pmr::memory_resource *allocator = std::pmr::get_default_resource()) -> import_result = 0;

protected:
    importer() noexcept = default;
};

} // namespace aeon::engine::import

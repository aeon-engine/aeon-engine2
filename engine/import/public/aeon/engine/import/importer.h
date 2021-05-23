// Distributed under the BSD 2-Clause License - Copyright 2019-2021 Robin Degen

#pragma once

#include <aeon/engine/import/import_result.h>
#include <aeon/engine/import/export.h>
#include <aeon/engine/core/types/path.h>
#include <memory_resource>

namespace aeon::engine::import
{

class importer
{
public:
    [[nodiscard]] AEON_ENGINE_IMPORT_EXPORT static auto create() -> std::unique_ptr<importer>;

    virtual ~importer() = default;

    importer(const importer &) = delete;
    auto operator=(const importer &) -> importer & = delete;

    importer(importer &&) noexcept = delete;
    auto operator=(importer &&) noexcept -> importer & = delete;

    [[nodiscard]] virtual auto import(const core::types::path &path) -> import_result = 0;

protected:
    importer() noexcept = default;
};

} // namespace aeon::engine::import

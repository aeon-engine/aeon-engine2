# Distributed under the BSD 2-Clause License - Copyright 2021 Robin Degen

include(GenerateExportHeader)

set(SOURCES
    private/material_data.cpp
    private/mesh_data.cpp
    private/resource_data.cpp
    private/scene_data.cpp
    private/scene_prefab_data.cpp
    private/texture_data.cpp
    public/aeon/engine/resources/material_data.h
    public/aeon/engine/resources/mesh_data.h
    public/aeon/engine/resources/resource_data.h
    public/aeon/engine/resources/scene_data.h
    public/aeon/engine/resources/scene_prefab_data.h
    public/aeon/engine/resources/texture_data.h
)

source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${SOURCES})

add_library(aeon_engine_resources SHARED
    ${SOURCES}
)

generate_export_header(aeon_engine_resources
    EXPORT_FILE_NAME public/aeon/engine/resources/export.h
)

set_target_properties(aeon_engine_resources PROPERTIES
    FOLDER engine
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
)

target_include_directories(aeon_engine_resources
    PRIVATE
        private
    PUBLIC
        public
        ${CMAKE_CURRENT_BINARY_DIR}/public
)

target_link_libraries(aeon_engine_resources
    PUBLIC
        aeon_engine_common
)

install(
    TARGETS aeon_engine_resources
    RUNTIME DESTINATION bin
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
)

# Distributed under the BSD 2-Clause License - Copyright 2021 Robin Degen

include(GenerateExportHeader)

set(SOURCES
    private/mesh.cpp
    public/aeon/renderer/mesh.h
)

source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${SOURCES})

add_library(aeon_engine_renderer SHARED
    ${SOURCES}
)

generate_export_header(aeon_engine_renderer
    EXPORT_FILE_NAME public/aeon/renderer/export.h
)

set_target_properties(aeon_engine_renderer PROPERTIES
    FOLDER engine
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
)

target_include_directories(aeon_engine_renderer
    PRIVATE
        private
    PUBLIC
        public
        ${CMAKE_CURRENT_BINARY_DIR}/public
)

target_link_libraries(aeon_engine_renderer
    aeon_engine_rhi
)

install(
    TARGETS aeon_engine_renderer
    RUNTIME DESTINATION bin
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
)

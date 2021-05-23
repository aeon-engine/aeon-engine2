# Distributed under the BSD 2-Clause License - Copyright 2021 Robin Degen

include(GenerateExportHeader)

set(SOURCES
    private/hal/default_file_manager.cpp
    private/hal/default_file_manager.h
    private/hal/file_manager.cpp
    public/aeon/engine/core/hal/file_manager.h
    public/aeon/engine/core/types/filter_type.h
    public/aeon/engine/core/types/path.h
    public/aeon/engine/core/types/vertex_data.h
)

source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${SOURCES})

add_library(aeon_engine_core SHARED
    ${SOURCES}
)

generate_export_header(aeon_engine_core
    EXPORT_FILE_NAME public/aeon/engine/core/export.h
)

set_target_properties(aeon_engine_core PROPERTIES
    FOLDER engine
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
)

target_include_directories(aeon_engine_core
    PRIVATE
        private
    PUBLIC
        public
        ${CMAKE_CURRENT_BINARY_DIR}/public
)

target_link_libraries(aeon_engine_core
    PUBLIC
        aeon_common
        aeon_math
        aeon_streams
)

install(
    TARGETS aeon_engine_core
    RUNTIME DESTINATION bin
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
)

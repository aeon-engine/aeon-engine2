# Distributed under the BSD 2-Clause License - Copyright 2021 Robin Degen

include(GenerateExportHeader)

set(SOURCES
    private/codecs/assimp/assimp_codec.cpp
    private/codecs/assimp/assimp_codec.h
    private/codecs/codec.h
    private/importer.cpp
    public/aeon/import/importer.h
)

source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${SOURCES})

add_library(aeon_engine_import SHARED
    ${SOURCES}
)

generate_export_header(aeon_engine_import
    EXPORT_FILE_NAME public/aeon/import/export.h
)

set_target_properties(aeon_engine_import PROPERTIES
    FOLDER engine
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
)

target_include_directories(aeon_engine_import
    PRIVATE
        private
    PUBLIC
        public
        ${CMAKE_CURRENT_BINARY_DIR}/public
)

target_link_libraries(aeon_engine_import
    PUBLIC
        aeon_engine_resources
    PRIVATE
        aeon_streams
        assimp::assimp
)

install(
    TARGETS aeon_engine_import
    RUNTIME DESTINATION bin
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
)

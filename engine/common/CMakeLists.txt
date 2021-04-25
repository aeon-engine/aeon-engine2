# Distributed under the BSD 2-Clause License - Copyright 2021 Robin Degen

set(SOURCES
    private/dummy.cpp
    public/aeon/engine/common/filter_type.h
    public/aeon/engine/common/format.h
    public/aeon/engine/common/vertex_data.h
)

source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${SOURCES})

add_library(aeon_engine_common STATIC
    ${SOURCES}
)

set_target_properties(aeon_engine_common PROPERTIES
    FOLDER engine
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
)

target_include_directories(aeon_engine_common
    PRIVATE
        private
    PUBLIC
        public
)

target_link_libraries(aeon_engine_common
    PUBLIC
        aeon_math
)

install(
    TARGETS aeon_engine_common
    RUNTIME DESTINATION bin
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
)

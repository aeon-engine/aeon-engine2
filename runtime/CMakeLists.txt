# Distributed under the BSD 2-Clause License - Copyright 2012-2021 Robin Degen

set(SOURCES
    private/main.cpp
)

source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${SOURCES})

add_executable(aeon_engine_runtime
    ${SOURCES}
)

set_target_properties(aeon_engine_runtime PROPERTIES
    FOLDER runtime
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
)

target_include_directories(aeon_engine_runtime
    PRIVATE
        private
)

target_link_libraries(aeon_engine_runtime
    aeon_engine_rhi
)

add_dependencies(aeon_engine_runtime aeon_engine_rhi_dx11)

# Distributed under the BSD 2-Clause License - Copyright 2019 Robin Degen

include(GenerateExportHeader)

set(SOURCES
    private/resource.cpp
    private/rhi.cpp
    public/aeon/rhi/blend_state.h
    public/aeon/rhi/bound_shader_state.h
    public/aeon/rhi/buffer.h
    public/aeon/rhi/context.h
    public/aeon/rhi/depth_stencil_state.h
    public/aeon/rhi/device.h
    public/aeon/rhi/filter_type.h
    public/aeon/rhi/format.h
    public/aeon/rhi/graphics_pipeline_state.h
    public/aeon/rhi/input_layout_description.h
    public/aeon/rhi/primitive_topology.h
    public/aeon/rhi/rasterizer_state.h
    public/aeon/rhi/resource.h
    public/aeon/rhi/resource_data.h
    public/aeon/rhi/rhi.h
    public/aeon/rhi/rhi_plugin.h
    public/aeon/rhi/sampler_state.h
    public/aeon/rhi/shader.h
    public/aeon/rhi/shader_resource_view.h
    public/aeon/rhi/texture.h
    public/aeon/rhi/viewport.h
    public/aeon/rhi/wrap_mode.h
)

source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${SOURCES})

add_library(aeon_engine_rhi SHARED
    ${SOURCES}
)

generate_export_header(aeon_engine_rhi
    EXPORT_FILE_NAME public/aeon/rhi/export.h
)

set_target_properties(aeon_engine_rhi PROPERTIES
    FOLDER engine
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
)

target_include_directories(aeon_engine_rhi
    PRIVATE
        private
    PUBLIC
        public
        ${CMAKE_CURRENT_BINARY_DIR}/public
)

target_link_libraries(aeon_engine_rhi
    aeon_common
    aeon_imaging
    aeon_math
    aeon_plugins
    aeon_streams
    aeon_platform
)

install(
    TARGETS aeon_engine_rhi
    RUNTIME DESTINATION bin
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
)

add_subdirectory(tests)

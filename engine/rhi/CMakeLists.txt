# Distributed under the BSD 2-Clause License - Copyright 2021 Robin Degen

include(GenerateExportHeader)

set(SOURCES
    private/rhi.cpp
    public/aeon/engine/rhi/blend_state.h
    public/aeon/engine/rhi/bound_shader_state.h
    public/aeon/engine/rhi/buffer.h
    public/aeon/engine/rhi/context.h
    public/aeon/engine/rhi/depth_stencil_state.h
    public/aeon/engine/rhi/device.h
    public/aeon/engine/rhi/graphics_pipeline_state.h
    public/aeon/engine/rhi/input_layout_description.h
    public/aeon/engine/rhi/primitive_topology.h
    public/aeon/engine/rhi/rasterizer_state.h
    public/aeon/engine/rhi/resource.h
    public/aeon/engine/rhi/resource_data.h
    public/aeon/engine/rhi/rhi.h
    public/aeon/engine/rhi/rhi_plugin.h
    public/aeon/engine/rhi/sampler_state.h
    public/aeon/engine/rhi/shader.h
    public/aeon/engine/rhi/shader_resource_view.h
    public/aeon/engine/rhi/texture.h
    public/aeon/engine/rhi/viewport.h
    public/aeon/engine/rhi/wrap_mode.h
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
    PUBLIC
        aeon_engine_common
        aeon_platform
        aeon_math
        aeon_imaging
        aeon_plugins
    PRIVATE
        aeon_common
        aeon_streams
)

install(
    TARGETS aeon_engine_rhi
    RUNTIME DESTINATION bin
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
)

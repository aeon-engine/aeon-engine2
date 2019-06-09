# Distributed under the BSD 2-Clause License - Copyright 2019 Robin Degen

include(GenerateExportHeader)

set(SOURCES
    private/checked_hresult.h
    private/dx11_context.cpp
    private/dx11_context.h
    private/dx11_device.cpp
    private/dx11_device.h
    private/dx11_rhi_bound_shader_state.h
    private/dx11_rhi_buffer.h
    private/dx11_rhi_depth_stencil_state.h
    private/dx11_rhi_blend_state.h
    private/dx11_rhi_graphics_pipeline_state.h
    private/dx11_rhi_plugin.cpp
    private/dx11_rhi_plugin.h
    private/dx11_rhi_rasterizer_state.h
    private/dx11_rhi_converters.h
    private/dx11_rhi_sampler.h
    private/dx11_rhi_shader.h
    private/dx11_rhi_shader_resource_view.h
    private/dx11_rhi_texture.h
    private/dx11_rhi_blend_state.h
)

source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${SOURCES})

########################################################################################################################

add_library(aeon_engine_rhi_dx11 SHARED
    ${SOURCES}
)

set_target_properties(aeon_engine_rhi_dx11 PROPERTIES
    FOLDER engine
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
)

target_include_directories(aeon_engine_rhi_dx11
    PRIVATE
        private
)

target_link_libraries(aeon_engine_rhi_dx11
    aeon_engine_rhi
    aeon_plugins
    dxgi
    d3d11
)

target_compile_definitions(aeon_engine_rhi_dx11
    PRIVATE
        AEON_RHI_DX11_ENABLE_ERROR_CHECKING
)

install(
    TARGETS aeon_engine_rhi_dx11
    RUNTIME DESTINATION bin
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
)

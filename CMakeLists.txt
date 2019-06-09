# Distributed under the BSD 2-Clause License - Copyright 2019 Robin Degen

cmake_minimum_required(VERSION 3.13)

if (DEFINED ENV{AEON_ENGINE_PROJECT_NAME})
    project($ENV{AEON_ENGINE_PROJECT_NAME})
else ()
    project(AeonEngine)
endif ()

# Don't allow any circular dependencies. Not even for static libraries.
set_property(GLOBAL PROPERTY GLOBAL_DEPENDS_NO_CYCLES 1)

set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/dep/cmake/;${CMAKE_MODULE_PATH}")

include(Dependencies)
handle_local_dependencies_file()
handle_dependencies_file("${CMAKE_SOURCE_DIR}/dep/libaeon/dependencies.txt")

include(CompilerFlags)

if (MSVC)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /wd4251")
endif ()

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

set(CMAKE_DEBUG_POSTFIX "_d")

set(CMAKE_CXX_STANDARD 20)

include(ComponentUtils)
enable_component(common)
enable_component(imaging)
enable_component(math)
enable_component(plugins)
enable_component(streams)
enable_component(gl)
enable_component(gl_utils)
enable_component(platform)

set(AEON_ENABLE_TESTING ON CACHE BOOL "")

################################################################################

# TODO: This is needed for the spir-v compiler; which should be part of the engine sources instead
find_package(LunarGVulkanSDK)

add_subdirectory(dep)
add_subdirectory(engine)
add_subdirectory(runtime)

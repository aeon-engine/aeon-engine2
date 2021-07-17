# Distributed under the BSD 2-Clause License - Copyright 2021 Robin Degen

cmake_minimum_required(VERSION 3.13)

if (DEFINED ENV{AEON_ENGINE_PROJECT_NAME})
    project($ENV{AEON_ENGINE_PROJECT_NAME})
else ()
    project(AeonEngine)
endif ()

# Don't allow any circular dependencies. Not even for static libraries.
set_property(GLOBAL PROPERTY GLOBAL_DEPENDS_NO_CYCLES 1)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/dep/cmake/")
list(APPEND CMAKE_MODULE_PATH "${CMAKE_BINARY_DIR}")

include(CompilerFlags)

if (EXISTS ${CMAKE_BINARY_DIR}/conanbuildinfo_multi.cmake)
    message("Using multi-target conan configuration.")
    include(conanbuildinfo_multi)
else ()
    message("Using single target conan configuration.")
    include(conanbuildinfo)
endif ()

conan_basic_setup(TARGETS)

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
enable_component(platform)

set(AEON_ENABLE_TESTING ON CACHE BOOL "")

################################################################################

add_subdirectory(dep)
add_subdirectory(engine)
add_subdirectory(runtime)

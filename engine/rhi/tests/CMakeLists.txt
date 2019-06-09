# Copyright (c) 2019 Robin Degen

include(Unittests)

add_unit_test_suite(
    NO_GTEST_MAIN
    TARGET test_aeon_engine_rhi
    SOURCES
        main.cpp
        test_rhi.cpp
    LIBRARIES aeon_engine_rhi
    FOLDER engine/tests
)

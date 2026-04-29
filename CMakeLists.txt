# ========================================
# Name: Guilherme Armin Da Silva Anton
# UFID: 2641-9801
# COP3530 Project 2 - GeoPulse
# File: CMakeLists.txt
# Purpose: Builds the GeoPulse executable and Catch2 test suite.
# ========================================

cmake_minimum_required(VERSION 3.20)

project(GeoPulse VERSION 0.2.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

option(GEOPULSE_WARNINGS_AS_ERRORS "Treat warnings as errors" ON)
option(GEOPULSE_ENABLE_TESTS "Build GeoPulse tests" ON)

function(apply_geopulse_warnings target_name)
    if(MSVC)
        target_compile_options(${target_name} PRIVATE /W4)
        if(GEOPULSE_WARNINGS_AS_ERRORS)
            target_compile_options(${target_name} PRIVATE /WX)
        endif()
    else()
        target_compile_options(${target_name} PRIVATE
            -Wall -Wextra -Wpedantic)
        if(GEOPULSE_WARNINGS_AS_ERRORS)
            target_compile_options(${target_name} PRIVATE -Werror)
        endif()
    endif()
endfunction()

file(COPY "${CMAKE_CURRENT_SOURCE_DIR}/data/samples"
    DESTINATION "${CMAKE_CURRENT_BINARY_DIR}/data")

file(GLOB_RECURSE GEOPULSE_LIB_SOURCES CONFIGURE_DEPENDS
    "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")
list(FILTER GEOPULSE_LIB_SOURCES EXCLUDE REGEX ".*/src/main\\.cpp$")

add_library(geopulse_lib ${GEOPULSE_LIB_SOURCES})
target_include_directories(geopulse_lib
    PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include"
    PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/src")
apply_geopulse_warnings(geopulse_lib)

add_executable(Main "${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp")
set_target_properties(Main PROPERTIES OUTPUT_NAME geopulse)
target_link_libraries(Main PRIVATE geopulse_lib)

if(GEOPULSE_ENABLE_TESTS)
    enable_testing()

    add_library(Catch2Local STATIC
        "${CMAKE_CURRENT_SOURCE_DIR}/tests/catch2/catch_amalgamated.cpp")
    target_include_directories(Catch2Local
        PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/tests/catch2")

    if(MSVC)
        target_compile_options(Catch2Local PRIVATE /Od)
    else()
        target_compile_options(Catch2Local PRIVATE -O0 -g0)
    endif()

    file(GLOB_RECURSE GEOPULSE_TEST_SOURCES CONFIGURE_DEPENDS
        "${CMAKE_CURRENT_SOURCE_DIR}/tests/*.cpp")
    list(FILTER GEOPULSE_TEST_SOURCES EXCLUDE REGEX
        ".*/tests/catch2/catch_amalgamated\\.cpp$")

    add_executable(Tests ${GEOPULSE_TEST_SOURCES})
    set_target_properties(Tests PROPERTIES OUTPUT_NAME geopulse_tests)
    target_link_libraries(Tests PRIVATE geopulse_lib Catch2Local)
    target_include_directories(Tests PRIVATE
        "${CMAKE_CURRENT_SOURCE_DIR}/tests")
    target_compile_definitions(Tests PRIVATE
        GEOPULSE_SOURCE_DIR="${CMAKE_CURRENT_SOURCE_DIR}")
    apply_geopulse_warnings(Tests)

    list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/tests/catch2")
    include(Catch)
    catch_discover_tests(Tests)
endif()

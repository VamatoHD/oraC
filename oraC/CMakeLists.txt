cmake_minimum_required(VERSION 3.10)
project(oraC LANGUAGES C)

file(GLOB_RECURSE SOURCES "src/*.c")

add_library(oraC STATIC ${SOURCES})

target_include_directories(oraC PUBLIC 
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)

add_library(oraC::oraC ALIAS oraC)
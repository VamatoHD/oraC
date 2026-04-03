cmake_minimum_required(VERSION 3.10)
project(oraC LANGUAGES C)

file(GLOB_RECURSE SOURCES "src/*.c")
add_library(oraC STATIC ${SOURCES})

target_include_directories(oraC PUBLIC 
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)

add_library(oraC::oraC ALIAS oraC)

#For testing
enable_testing()
add_executable(oraC_test tests/test_vector.c)
target_link_libraries(oraC_test PRIVATE oraC::oraC)
add_test(NAME BaseTest COMMAND oraC_test)
cmake_minimum_required(VERSION 4.0)

project(cpp_utils LANGUAGES CXX)

add_library(cpp_utils INTERFACE)

target_include_directories(cpp_utils
        INTERFACE
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)
target_compile_features(cpp_utils
        INTERFACE
        cxx_std_23
)

add_library(cpp_utils::cpp_utils ALIAS cpp_utils)
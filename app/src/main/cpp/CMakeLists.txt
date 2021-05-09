cmake_minimum_required(VERSION 3.10.2)

project("bypass_dlfunctions_sample")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fno-stack-protector")

set(bypass_dlfcn_root_dir ${CMAKE_CURRENT_SOURCE_DIR}/../../../../lib)
add_subdirectory(${bypass_dlfcn_root_dir} bypasss_dlfcn)

include_directories(
        ${bypass_dlfcn_root_dir}/include/
)

add_library(
        bypass_dlfunctions_sample
        SHARED
        sample.cpp)

find_library(
        log-lib
        log)

target_link_libraries(
        bypass_dlfunctions_sample
        bypass_dlfcn
        ${log-lib})
project(twlib)

cmake_minimum_required(VERSION 2.8)


set(CMAKE_CXX_FLAGS "-std=c++0x")
set(SRC "src")
set(HDR "include")
set(LIST "")
include_directories(${HDR})


file(GLOB_RECURSE LIST "${HDR}/*.*")
add_library(twl SHARED ${LIST})
set_target_properties(twl PROPERTIES LINKER_LANGUAGE CXX)

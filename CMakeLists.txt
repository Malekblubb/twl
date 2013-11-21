project(twlib)

cmake_minimum_required(VERSION 2.8)


set(CMAKE_CXX_FLAGS "-std=c++0x")
set(SRC "src")
set(HDR "include")
set(EXT_MLK "external/mlk/include")
set(EXT_TW "external/teeworlds/src")
set(LIST "")
include_directories(${HDR} ${EXT_MLK} ${EXT_TW})


file(GLOB_RECURSE LIST "${HDR}/*.*")
add_library(twl SHARED ${LIST})
set_target_properties(twl PROPERTIES LINKER_LANGUAGE CXX)

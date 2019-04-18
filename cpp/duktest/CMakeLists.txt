# CMake 最低版本号要求
cmake_minimum_required (VERSION 2.8)
# 项目信息
project (duktest)
include_directories("../libs/duktape")
aux_source_directory(. DIR_SRCS)
add_executable(duk ${DIR_SRCS})

target_link_libraries(duk duklib)
cmake_minimum_required(VERSION 2.8)
project(mbroad)

INCLUDE_DIRECTORIES( include )
AUX_SOURCE_DIRECTORY(src DIR_SRCS)

ADD_EXECUTABLE(${PROJECT_NAME} ${DIR_SRCS})
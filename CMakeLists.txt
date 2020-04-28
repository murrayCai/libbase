cmake_minimum_required(VERSION 3.16)
project(libbase C)
set(CMAKE_INSTALL_PREFIX /usr)

SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR})
SET(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR})

set(CMAKE_BUILD_TYPE "Debug")
# set(CMAKE_DEBUG_POSTFIX "_d")

add_subdirectory(src)
add_subdirectory(test)

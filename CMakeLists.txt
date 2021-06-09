cmake_minimum_required(VERSION 3.16)
project(libmc C)
set(CMAKE_INSTALL_PREFIX /usr)

#SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin/debug)
#SET(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin/debug)

#set(CMAKE_BUILD_TYPE "Debug")
# set(CMAKE_DEBUG_POSTFIX "_d")

include_directories("./include")
SET(CMAKE_C_FLAGS "-std=c89 -gdwarf-4 -g3")

add_subdirectory(src)
#add_subdirectory(test)

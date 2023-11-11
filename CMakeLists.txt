cmake_minimum_required(VERSION 3.23)
project(RK3588_NCNN)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_SYSTEM_NAME Linux)
set(CMAKE_SYSTEM_PROCESSOR arm)

# 设置输出bin文件路径
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin)
set(CMAKE_BUILD_TYPE Debug)

set(COMPILER "/usr/local/gcc-arm-8.3-2019.03-x86_64-arm-linux-gnueabihf")

set(CMAKE_C_COMPILER "${COMPILER}/bin/arm-linux-gnueabihf-gcc")
set(CMAKE_CXX_COMPILER "${COMPILER}/bin/arm-linux-gnueabihf-g++")

set(CMAKE_FIND_ROOT_PATH "${COMPILER}/arm-linux-gnueabihf")

set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -march=armv7-a -mfloat-abi=hard -mfpu=neon  -fopenmp -Wno-psabi")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -march=armv7-a -mfloat-abi=hard -mfpu=neon  -fopenmp -Wno-psabi")

# cache flags
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS}" CACHE STRING "c flags")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}" CACHE STRING "c++ flags")

include(${CMAKE_SOURCE_DIR}/cmake/3dparty.cmake)

add_executable(${PROJECT_NAME} main.cpp)
target_link_libraries(${PROJECT_NAME}  ncnn ${OpenCV_LIBS} ${FFMEPG_LIB})

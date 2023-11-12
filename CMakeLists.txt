cmake_minimum_required(VERSION 3.23)
project(RK3588_NCNN)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_SYSTEM_NAME Linux)
set(CMAKE_SYSTEM_PROCESSOR arm)

# SDK 链接库
add_subdirectory(${CMAKE_SOURCE_DIR}/SDK/common)

# 设置输出bin文件路径
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin)
set(CMAKE_BUILD_TYPE Debug)

include(${CMAKE_SOURCE_DIR}/cmake/compiler.cmake)
include(${CMAKE_SOURCE_DIR}/cmake/3dparty.cmake)
add_executable(${PROJECT_NAME} main.cpp)
target_link_libraries(${PROJECT_NAME}  ncnn ${OpenCV_LIBS} ${FFMEPG_LIB} common)

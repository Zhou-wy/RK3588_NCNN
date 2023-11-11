cmake_minimum_required(VERSION 3.15)
project(common)

#include(${CMAKE_SOURCE_DIR}/cmake/3dparty.cmake)

file(GLOB_RECURSE CURRENT_HEADERS  *.h *.hpp)
file(GLOB CURRENT_SOURCES  *.c *.cpp)

source_group("Include" FILES ${CURRENT_HEADERS})
source_group("Source" FILES ${CURRENT_SOURCES})

# 创建静态库
add_library(${PROJECT_NAME} STATIC ${CURRENT_HEADERS} ${CURRENT_SOURCES})

# 链接OpenCV库
target_link_libraries(${PROJECT_NAME} ${OpenCV_LIBS})

cmake_minimum_required(VERSION 3.23)
project(RK3588_NCNN)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_SYSTEM_NAME Linux)
set(CMAKE_SYSTEM_PROCESSOR arm)

# SDK 链接库
add_subdirectory(${CMAKE_SOURCE_DIR}/SDK/common)

set(CMAKE_BUILD_TYPE Debug)
set(SDK_LIB ${SDK_LIB} common)

include(${CMAKE_SOURCE_DIR}/cmake/compiler.cmake)
include(${CMAKE_SOURCE_DIR}/cmake/3dparty.cmake)
add_executable(${PROJECT_NAME} main.cpp)
target_link_libraries(${PROJECT_NAME}  ncnn ${OpenCV_LIBS} ${FFMEPG_LIB} ${SDK_LIB})

## 测试用例
# add_executable(test_tensor ${CMAKE_SOURCE_DIR}/example/test_tensor.cpp)
# target_link_libraries(test_tensor ncnn ${OpenCV_LIBS} ${FFMEPG_LIB} ${SDK_LIB})

add_executable(test_logger ${CMAKE_SOURCE_DIR}/example/test_logger.cpp)
target_link_libraries(test_logger ncnn ${OpenCV_LIBS} ${FFMEPG_LIB} ${SDK_LIB})

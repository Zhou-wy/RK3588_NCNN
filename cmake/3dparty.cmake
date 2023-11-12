
if(CMAKE_SYSTEM_NAME  MATCHES "Darwin")
    message("Building on macOS")
    set(NCNN_DIR "${PROJECT_SOURCE_DIR}/3dparty/darwin_ncnn")
    set(CMAKE_PREFIX_PATH "${PROJECT_SOURCE_DIR}/3dparty/darwin_opencv/lib/cmake/opencv4")
    set(FFMEPG "${PROJECT_SOURCE_DIR}/3dparty/darwin_ffmpeg")

elseif(CMAKE_SYSTEM_NAME MATCHES "Linux")
    message("Building on Linux")
    set(NCNN_DIR "${PROJECT_SOURCE_DIR}/3dparty/arm_ncnn")
    set(CMAKE_PREFIX_PATH "${PROJECT_SOURCE_DIR}/3dparty/arm_opencv/lib/cmake/opencv4")
    set(FFMEPG "${PROJECT_SOURCE_DIR}/3dparty/rk_opencv_depend")

    set(COMPILER "/usr/local/gcc-arm-8.3-2019.03-x86_64-arm-linux-gnueabihf")
    set(CMAKE_C_COMPILER "${COMPILER}/bin/arm-linux-gnueabihf-gcc")
    set(CMAKE_CXX_COMPILER "${COMPILER}/bin/arm-linux-gnueabihf-g++")
    set(CMAKE_FIND_ROOT_PATH "${COMPILER}/arm-linux-gnueabihf")
    set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
    set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
    set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -march=armv7-a -mfloat-abi=hard -mfpu=neon  -fopenmp -Wno-psabi")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -march=armv7-a -mfloat-abi=hard -mfpu=neon  -fopenmp -Wno-psabi")
    set(CMAKE_BINARY_DIR ${PROJECT_SOURCE_DIR}/arm_linux_rk3588_debug)
    # cache flags
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS}" CACHE STRING "c flags")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}" CACHE STRING "c++ flags")
else()

    message(FATAL_ERROR "Unsupported platform: ${CMAKE_SYSTEM_NAME}")
endif()

include_directories(${NCNN_DIR}/include)
link_directories(${NCNN_DIR}/lib)
message(STATUS "NCNN libdir:${NCNN_DIR}/lib")
message(STATUS "NCNN includedir:${NCNN_DIR}/include")

find_package(OpenCV 4 REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})
message(STATUS "OpenCV version:${OpenCV_VERSION}")
message(STATUS "OpenCV libdir:${OpenCV_LIBS}")
message(STATUS "OpenCV includedir:${OpenCV_INCLUDE_DIRS}")

include_directories(${FFMEPG}/include)
link_directories(${FFMEPG}/lib)
set(FFMEPG_LIB ${FFMEPG_LIB} avcodec  avdevice  avfilter  avformat  avutil avresample postproc  swresample  swscale x264 xvidcore z)
message(STATUS "FFMEPG libdir:${FFMEPG}/lib")
message(STATUS "FFMEPG includedir:${FFMEPG}/include")


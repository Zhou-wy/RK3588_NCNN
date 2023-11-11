
set(NCNN_DIR "${PROJECT_SOURCE_DIR}/3dparty/arm_ncnn")
include_directories(${NCNN_DIR}/include)
link_directories(${NCNN_DIR}/lib)
message(STATUS "NCNN libdir:${NCNN_DIR}/lib")
message(STATUS "NCNN includedir:${NCNN_DIR}/include")


set(CMAKE_PREFIX_PATH "${PROJECT_SOURCE_DIR}/3dparty/arm_opencv/lib/cmake/opencv4")
find_package(OpenCV 4.5.5 REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})
message(STATUS "OpenCV version:${OpenCV_VERSION}")
message(STATUS "OpenCV libdir:${OpenCV_LIBS}")
message(STATUS "OpenCV includedir:${OpenCV_INCLUDE_DIRS}")


set(FFMEPG "${PROJECT_SOURCE_DIR}/3dparty/rk_opencv_depend")
include_directories(${FFMEPG}/include)
link_directories(${FFMEPG}/lib)
set(FFMEPG_LIB ${FFMEPG_LIB} avcodec  avdevice  avfilter  avformat  avutil avresample postproc  swresample  swscale x264 xvidcore z)
message(STATUS "FFMEPG libdir:${FFMEPG}/lib")
message(STATUS "FFMEPG includedir:${FFMEPG}/include")


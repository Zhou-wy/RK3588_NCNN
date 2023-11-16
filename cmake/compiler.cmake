
if(APPLE)
    # macOS-specific settings
    message("compiler from macOS")
    set(COMPILER "/Library/Developer/CommandLineTools/")
    set(CMAKE_C_COMPILER "${COMPILER}/usr/bin/gcc")
    set(CMAKE_CXX_COMPILER "${COMPILER}/usr/bin/g++")
    # 设置输出bin文件路径
    set(EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/apple_bin)
    set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/apple_bin)

    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wno-deprecated-declarations")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-deprecated-declarations")

elseif(UNIX)
    # Linux-specific settings
    message("compiler from Linux")
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

    # 设置输出bin文件路径
    set(EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/rk3588_bin)
    set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/rk3588_bin)
else()
    message(FATAL_ERROR "Unsupported platform: ${CMAKE_SYSTEM_NAME}")
endif()

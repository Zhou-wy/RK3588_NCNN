
if(APPLE)
    # macOS-specific settings
    message("compiler from macOS")
    set(COMPILER "/Library/Developer/CommandLineTools/")
    set(CMAKE_C_COMPILER "${COMPILER}/usr/bin/gcc")
    set(CMAKE_CXX_COMPILER "${COMPILER}/usr/bin/g++")

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

else()
    message(FATAL_ERROR "Unsupported platform: ${CMAKE_SYSTEM_NAME}")
endif()

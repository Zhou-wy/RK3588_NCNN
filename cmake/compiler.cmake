
if(CMAKE_SYSTEM_NAME MATCHES "Darwin")
    # macOS-specific settings
    message("compiler from macOS")
    set(COMPILER "/Library/Developer/CommandLineTools/")
    set(CMAKE_C_COMPILER "${COMPILER}/usr/bin/gcc")
    set(CMAKE_CXX_COMPILER "${COMPILER}/usr/bin/g++")

elseif(CMAKE_SYSTEM_NAME MATCHES "Linux")
    # Linux-specific settings
    message("compiler from Linux")
    set(COMPILER "/usr/local/gcc-arm-8.3-2019.03-x86_64-arm-linux-gnueabihf")
    set(CMAKE_C_COMPILER "${COMPILER}/bin/arm-linux-gnueabihf-gcc")
    set(CMAKE_CXX_COMPILER "${COMPILER}/bin/arm-linux-gnueabihf-g++")
    set(CMAKE_FIND_ROOT_PATH "${COMPILER}/arm-linux-gnueabihf")

else()
    message(FATAL_ERROR "Unsupported platform: ${CMAKE_SYSTEM_NAME}")
endif()
cmake_minimum_required(VERSION 3.10)

project(java-frida)

set(CMAKE_CXX_STANDARD 11)

if(UNIX AND NOT APPLE)
    set(LINUX TRUE)
endif()

include(GNUInstallDirs)
find_package(JNI REQUIRED)
include_directories(${JNI_INCLUDE_DIRS})
include_directories(include)

add_library(frida-core STATIC IMPORTED)
if (APPLE)
    set_target_properties(frida-core PROPERTIES IMPORTED_LOCATION ${CMAKE_SOURCE_DIR}/lib/libfrida-core-macos-arm64.a)
elseif(LINUX)
    set_target_properties(frida-core PROPERTIES IMPORTED_LOCATION ${CMAKE_SOURCE_DIR}/lib/libfrida-core-linux-x86_64.a)
endif()

add_library(frida-integration SHARED ${CMAKE_SOURCE_DIR}/src/frida-integration.c)
if(APPLE)
    target_link_libraries(frida-integration PRIVATE frida-core bsm resolv)
    set_target_properties(frida-integration PROPERTIES LINK_FLAGS "-Wl,-framework,Foundation,-framework,AppKit")
elseif(LINUX)
    target_link_libraries(frida-integration PRIVATE frida-core)
    target_link_options(frida-integration PRIVATE -Wl,-z,noexecstack)
endif()

add_executable(example src/example.c)


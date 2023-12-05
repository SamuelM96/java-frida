cmake_minimum_required(VERSION 3.10)

project(java-frida)

set(CMAKE_CXX_STANDARD 11)

include(GNUInstallDirs)
find_package(JNI REQUIRED)
include_directories(${JNI_INCLUDE_DIRS})
include_directories(include)

add_library(frida-core STATIC IMPORTED)
set_target_properties(frida-core PROPERTIES IMPORTED_LOCATION ${CMAKE_SOURCE_DIR}/include/libfrida-core.a)

add_library(frida-integration SHARED ${CMAKE_SOURCE_DIR}/src/frida-integration.c)
target_link_libraries(frida-integration PRIVATE frida-core)
target_link_options(frida-integration PRIVATE -Wl,-z,noexecstack)

add_executable(example src/example.c)


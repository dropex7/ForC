cmake_minimum_required(VERSION 3.10)
project(untitled)

set(CMAKE_CXX_STANDARD 11)

find_package(PkgConfig REQUIRED)
pkg_check_modules(LIBXML++ REQUIRED libxml++-2.6)

add_executable(untitled main.cpp)

target_link_libraries(untitled ${LIBXML++_LIBRARIES})
target_include_directories(untitled PUBLIC ${LIBXML++_INCLUDE_DIRS})
target_compile_options(untitled PUBLIC ${LIBXML++_CFLAGS_OTHER})

cmake_minimum_required(VERSION 3.10)
project(ftxclient)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "-Wall -Wfatal-errors -Wpedantic -Wextra -Wmissing-include-dirs -Wconversion  -Wsign-conversion -pthread")
add_compile_options(-Wall -Wfatal-errors -Wpedantic -Wextra -Wmissing-include-dirs -Wconversion -Wsign-conversion -pthread)

#-Werror -Wfatal-errors

set(CMAKE_CXX_FLAGS_DEBUG "-O0 -march=native -g")

set(Boost_USE_STATIC_LIBS OFF)
set(Boost_USE_STATIC_RUNTIME OFF)
set(Boost_USE_MULTITHREADED OFF)
find_package(Boost 1.71 REQUIRED)
link_directories(${Boost_LIBRARY_DIRS})
include_directories(SYSTEM ${Boost_INCLUDE_DIR})

include_directories(src)
include_directories(src/External/cpp-cryptlite/include/)

add_subdirectory(src/WS)
add_subdirectory(src/FIX)
add_subdirectory(src/Strategies)
add_subdirectory(src/Secrets)
add_subdirectory(src/Rest)
add_subdirectory(src/Utilities)
add_subdirectory(src)
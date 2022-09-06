cmake_minimum_required(VERSION 3.5 FATAL_ERROR)

project(Cache2Q VERSION 0.2 LANGUAGES CXX)

add_executable( Cache2Q
    src/main.cpp
    src/cache/cache.cpp
)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O2")

cmake_minimum_required(VERSION 3.20)
project(aura-engine)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(aura-engine STATIC
  src/core.cpp
  src/input.cpp
  src/renderer.cpp
  aura-libs/aura-glad/src/glad.c
)

target_include_directories(aura-engine
  PUBLIC
    include/
    aura-libs/aura-glad/include
)


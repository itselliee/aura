cmake_minimum_required(VERSION 3.20)

project(aura C CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(src/thirdparty/include)

add_executable(aura src/main.cpp
        src/thirdparty/lib/src/glad.c
        src/window/IWindow.h
        src/application/Application.h
        src/render/Renderer.h
)

find_package(glfw3 REQUIRED)
find_package(OpenGL REQUIRED)

target_link_libraries(aura PRIVATE glfw OpenGL::GL)
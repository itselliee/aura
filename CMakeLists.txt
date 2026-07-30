cmake_minimum_required(VERSION 3.20)
project(Aura)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(GLFW_BUILD_DOCS OFF CACHE INTERNAL "")
set(GLFW_BUILD_TESTS OFF CACHE INTERNAL "")
set(GLFW_BUILD_EXAMPLES OFF CACHE INTERNAL "")
add_subdirectory(third-party/glfw)

add_library(glad STATIC third-party/glad/lib/src/glad.c)
target_include_directories(glad PUBLIC third-party/glad/include)

add_library(imgui STATIC
        third-party/imgui/imgui.cpp
        third-party/imgui/imgui_demo.cpp
        third-party/imgui/imgui_draw.cpp
        third-party/imgui/imgui_tables.cpp
        third-party/imgui/imgui_widgets.cpp
        third-party/imgui/backends/imgui_impl_glfw.cpp
        third-party/imgui/backends/imgui_impl_opengl3.cpp
)
target_include_directories(imgui PUBLIC
        third-party/imgui
        third-party/imgui/backends
        third-party/glad/include
)
target_link_libraries(imgui PUBLIC glfw)

add_library(engine STATIC
        aura-engine/src/application.cpp
        aura-engine/src/window.cpp
        aura-engine/include/input.h
)

target_include_directories(engine PUBLIC aura-engine/include)

target_include_directories(engine PRIVATE third-party/imgui)

target_link_libraries(engine PRIVATE glfw glad)

add_executable(aura-editor
        aura-editor/src/main.cpp
        aura-editor/include/panel-layer.h

)

target_link_libraries(aura-editor PRIVATE
        engine
        imgui
)


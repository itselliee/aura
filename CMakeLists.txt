# Comments are littered around in this purely for organization, I cant read it properly without them.

cmake_minimum_required(VERSION 3.20)
project(aura)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# --== GLFW Environmental Variables ==--

set(GLFW_BUILD_DOCS OFF CACHE INTERNAL "")
set(GLFW_BUILD_TESTS OFF CACHE INTERNAL "")
set(GLFW_BUILD_EXAMPLES OFF CACHE INTERNAL "")
add_subdirectory(third-party/glfw)

# --== GLAD Library ==--

add_library(glad STATIC third-party/glad/lib/src/glad.c)
target_include_directories(glad PUBLIC third-party/glad/include)

# --== IMGUI Library ==--

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
        third-party/glad/include # Need this for OGL render
)
target_link_libraries(imgui PUBLIC glfw)

# --== Aura Engine Library (Hey! This is our one!) ==--
add_library(aura-core STATIC
        engine/src/app.cpp
        engine/src/input_system.cpp
        engine/src/internal_layer_stack.cpp
        engine/src/layer_stack.cpp
        engine/src/renderer.cpp
        engine/src/window.cpp
)

## -= Third-party =-
target_include_directories(aura-core PUBLIC third-party/stb)
target_include_directories(aura-core PRIVATE third-party/imgui)
target_link_libraries(aura-core PRIVATE glfw glad)

## -= Our code =-
target_include_directories(aura-core PUBLIC engine/include)

# --== Aura Editor Executable (This is our one, and it actually returns the results! WOOO!)
add_executable(aura-editor
        editor/src/main.cpp
        editor/ext-layers/editor-panels/performance_panel.h
)

target_include_directories(aura-editor PRIVATE editor/ext-layers)

target_link_libraries(aura-editor PRIVATE
        aura-core
        imgui
        glad
)

# --== Post Setup ==--
add_custom_command(TARGET aura-editor POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${CMAKE_CURRENT_SOURCE_DIR}/editor/res"
        "$<TARGET_FILE_DIR:aura-editor>/res"
)
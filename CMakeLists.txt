cmake_minimum_required(VERSION 3.20)
project(aura)

option(ENABLE_ASAN "Enable AddressSanitizer + LeakSanitizer" OFF)
if(ENABLE_ASAN)
    add_compile_options(-fsanitize=address,undefined -fno-omit-frame-pointer -g)
    add_link_options(-fsanitize=address,undefined)
endif()

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# --== SDL3 Environmental Variables ==--

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/$<CONFIGURATION>")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/$<CONFIGURATION>")

set(SDL_TESTS OFF CACHE INTERNAL "")
set(SDL_EXAMPLES OFF CACHE INTERNAL "")
set(SDL_DOCS OFF CACHE INTERNAL "")
add_subdirectory(third-party/SDL EXCLUDE_FROM_ALL)

# --== Yaml-CPP Lib == --
add_subdirectory(third-party/yaml-cpp)

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
        third-party/imgui/backends/imgui_impl_sdl3.cpp
        third-party/imgui/backends/imgui_impl_opengl3.cpp
        third-party/imspinner/cimspinner.cpp
)
target_include_directories(imgui PUBLIC
        third-party/imgui
        third-party/imgui/backends
        third-party/imspinner/
        third-party/glad/include # Need this for OGL render
)
target_link_libraries(imgui PUBLIC SDL3::SDL3)

# --== Aura Engine Library (Hey! This is our one!) ==--
add_library(aura-core STATIC
        engine/src/app.cpp
        engine/src/input_system.cpp
        engine/src/internal_layer_stack.cpp
        engine/src/layer_stack.cpp
        engine/src/window.cpp
        engine/src/imgui_renderer.cpp
        engine/src/scene_renderer.cpp
)

## -= Third-party =-
target_include_directories(aura-core PUBLIC third-party/stb)
target_include_directories(aura-core PRIVATE third-party/imgui)
target_include_directories(aura-core PUBLIC third-party/glm)
target_link_libraries(aura-core PRIVATE SDL3::SDL3 glad) # SWAPPED: Swapped glfw for SDL3

if(APPLE)
    target_compile_definitions(aura-core PUBLIC IS_APPLE_PLATFORM)
elseif(UNIX AND NOT APPLE)
    target_compile_definitions(aura-core PUBLIC IS_LINUX_PLATFORM)
elseif(WIN32)
    target_compile_definitions(aura-core PUBLIC IS_WINDOWS_PLATFORM)
endif()

## -= Our code =-
target_include_directories(aura-core PUBLIC engine/include)

# --== Aura Editor Executable (This is our one, and it actually returns the results! WOOO!)
add_executable(aura-editor
        editor/src/main.cpp
        editor/ext-layers/panels.h
        editor/utils/theme_imgui.h
        editor/utils/yaml_to_scene_parser.cpp
        editor/utils/yaml_to_scene_parser.h
        editor/utils/render-triangle.cpp
)

target_include_directories(aura-editor PRIVATE editor/ext-layers)

target_link_libraries(aura-editor PRIVATE
        aura-core
        imgui
        glad
        yaml-cpp
)

# --== Post Setup ==--
add_custom_command(TARGET aura-editor POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${CMAKE_CURRENT_SOURCE_DIR}/editor/editor_res"
        "$<TARGET_FILE_DIR:aura-editor>/editor_res"
)

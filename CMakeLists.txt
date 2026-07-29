cmake_minimum_required(VERSION 3.20)

project(aura C CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 1. Configure GLFW options before adding its directory
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(GLFW_INSTALL OFF CACHE BOOL "" FORCE)
set(CMAKE_BUILD_TYPE Debug)


# 2. Add the bundled GLFW source code as a subproject
add_subdirectory(src/thirdparty/glfw)

set(IMGUI_DIR src/thirdparty/imgui)

# 3. Target definition
add_executable(aura
        src/main.cpp
        src/thirdparty/glad/lib/src/glad.c
        src/engine/generalImports.h
        src/engine/window/window.h
        src/engine/render/render.h
        src/engine/input/inputsys.h
        src/engine/event/eventsys.h
        src/app/app.h
        src/engine/input/input2text.h
        ${IMGUI_DIR}/imgui.cpp
        ${IMGUI_DIR}/imgui_draw.cpp
        ${IMGUI_DIR}/imgui_widgets.cpp
        ${IMGUI_DIR}/imgui_tables.cpp
        ${IMGUI_DIR}/imgui_demo.cpp
        ${IMGUI_DIR}/backends/imgui_impl_glfw.cpp
        ${IMGUI_DIR}/backends/imgui_impl_opengl3.cpp
        src/editor/imgui_panels/imgui_perf_panel.h
        src/editor/imgui_panels/imgui_perf_panel.cpp
        src/engine/imgui/pushToRenderStack.h
        src/engine/imgui/pushToRenderStack.cpp
        src/editor/imgui_panels/imgui_example_panel.cpp
        src/editor/imgui_panels/imgui_example_panel.h
)

# 4. Include directories (prefer target_include_directories over global include_directories)
target_include_directories(aura PRIVATE
        src/thirdparty/glad/include
        ${IMGUI_DIR}
        ${IMGUI_DIR}/backend
)

# 5. Find system OpenGL (required by GLAD / GLFW rendering)
find_package(OpenGL REQUIRED)

# 6. Link your target against the bundled GLFW target and OpenGL
target_link_libraries(aura PRIVATE
        glfw
        OpenGL::GL
)
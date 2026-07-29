cmake_minimum_required(VERSION 3.20)

project(aura C CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(GLFW_INSTALL OFF CACHE BOOL "" FORCE)
set(CMAKE_BUILD_TYPE Debug)

add_subdirectory(src/thirdparty/glfw)

set(IMGUI_DIR src/thirdparty/imgui)

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
        src/editor/imgui_panels/imgui_example_panel.cpp
        src/editor/imgui_panels/imgui_example_panel.h
        src/engine/render/render.cpp
        src/engine/window/window.cpp
        src/engine/imguiPanelManager/imgui_panel_manager.cpp
        src/engine/imguiPanelManager/imgui_panel_manager.h
        src/engine/shader/shader_compilation_handler.cpp
        src/engine/shader/shader_compilation_handler.h
)

target_include_directories(aura PRIVATE
        src/thirdparty/glad/include
        ${IMGUI_DIR}
        ${IMGUI_DIR}/backend
)

find_package(OpenGL REQUIRED)

target_link_libraries(aura PRIVATE
        glfw
        OpenGL::GL
)

add_custom_command(TARGET aura POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E make_directory
        $<TARGET_FILE_DIR:aura>/shaders
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/src/included_shaders
        $<TARGET_FILE_DIR:aura>/shaders
        COMMENT "Copying shaders to output directory"
)

install(TARGETS aura
        RUNTIME DESTINATION .
)

install(DIRECTORY src/included_shaders/
        DESTINATION shaders
)
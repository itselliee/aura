//
// Created by ellie on 7/31/26.
//

#include <iostream>
#include <ostream>

#include "../include/internal_layer_stack.h"
#include <glad/glad.h>

#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"

namespace aura_core {
    class renderer : public internal_layer {
    public:
        renderer(window *window) {
            m_window = window;
        }

        void on_attach() override {
            std::cout << "render: pipeline online" << std::endl;
            IMGUI_CHECKVERSION();
            ImGui::CreateContext();
            ImGuiIO& io = ImGui::GetIO();

            io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;

            ImGui_ImplGlfw_InitForOpenGL(m_window->get_window(), true);
            ImGui_ImplOpenGL3_Init();

            ImGui::StyleColorsDark();
        }

        void gl_render_stg() override {
            glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT);
        }

        void imgui_render_stg() override {
            ImGui_ImplOpenGL3_NewFrame();
            ImGui_ImplGlfw_NewFrame();
            ImGui::NewFrame();

            ImGui::DockSpaceOverViewport(0, nullptr, ImGuiDockNodeFlags_PassthruCentralNode);
        }

        void post_render() override {
            ImGui::Render();
            ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        }

        void on_detach() override {
            ImGui_ImplOpenGL3_Shutdown();
            ImGui_ImplGlfw_Shutdown();
            ImGui::DestroyContext();
            std::cout << "render: pipeline shutdown safely" << std::endl;
        }
    private:
        window * m_window;
    };
}

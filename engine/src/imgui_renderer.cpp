//
// Created by ellie on 7/31/26.
//

#include <iostream>
#include <ostream>

#include "../include/internal_layer_stack.h"

#include "backends/imgui_impl_sdl3.h"
#include "backends/imgui_impl_opengl3.h"

namespace aura_core {
    class imgui_renderer : public internal_layer {
    public:
        imgui_renderer(window *window) {
            m_window = window;
        }

        void on_attach() override {
            IMGUI_CHECKVERSION();
            ImGui::CreateContext();
            ImGuiIO& io = ImGui::GetIO();

            io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;

            ImGui_ImplSDL3_InitForOpenGL(m_window->get_window(), SDL_GL_GetCurrentContext());
            ImGui_ImplOpenGL3_Init("#version 330 core");

            ImGui::StyleColorsDark();
            std::cout << "imgui_render: pipeline online" << std::endl;
        }

        void gl_render_stg() override {
            glBindFramebuffer(GL_FRAMEBUFFER, 0);
            glClearColor(0.82f, 0.659f, 0.922f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        }

        void imgui_render_stg() override {
            ImGui_ImplOpenGL3_NewFrame();
            ImGui_ImplSDL3_NewFrame();
            ImGui::NewFrame();

            ImGui::DockSpaceOverViewport(0, nullptr, ImGuiDockNodeFlags_PassthruCentralNode);
        }

        void post_render() override {
            ImGui::Render();
            ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        }

        void on_detach() override {
            ImGui_ImplOpenGL3_Shutdown();
            ImGui_ImplSDL3_Shutdown();
            ImGui::DestroyContext();
            std::cout << "render: pipeline shutdown safely" << std::endl;
        }
    private:
        window * m_window;
    };
}

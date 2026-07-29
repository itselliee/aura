//
// Created by ellie on 7/29/26.
//

#include <iostream>
#include "layer.h"
#include "window.h"
#include "../../third-party/imgui/imgui.h"
#include "../../third-party/imgui/backends/imgui_impl_glfw.h"
#include "../../third-party/imgui/backends/imgui_impl_opengl3.h"

namespace aura {
    class render_pipeline : public layer {
    public:
        render_pipeline(window* window) : layer("render_pipeline") { local_window = window; }

        void on_attach() override {
            std::cout << "render pipeline running" << std::endl;
            IMGUI_CHECKVERSION();
            ImGui::CreateContext();
            ImGuiIO& io = ImGui::GetIO();
            io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
            ImGui::StyleColorsDark();

            ImGui_ImplGlfw_InitForOpenGL(local_window->glfw_window(), true);
            ImGui_ImplOpenGL3_Init("#version 330");
        }

        void on_detach() override {
            ImGui_ImplOpenGL3_Shutdown();
            ImGui_ImplGlfw_Shutdown();
            ImGui::DestroyContext();
        }

        void on_update(float deltaTime) override {}

        void on_render() override {
            ImGui_ImplOpenGL3_NewFrame();
            ImGui_ImplGlfw_NewFrame();
            ImGui::NewFrame();
            ImGui::DockSpaceOverViewport(0, nullptr, ImGuiDockNodeFlags_PassthruCentralNode);

            glClearColor(0.075f, 0.075f, 0.075f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        }

        void on_gui() override {
            ImGui::Render();
            ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

            // Required since you enabled ImGuiConfigFlags_ViewportsEnable
            ImGuiIO& io = ImGui::GetIO();
            if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable) {
                GLFWwindow* backup_context = glfwGetCurrentContext();
                ImGui::UpdatePlatformWindows();
                ImGui::RenderPlatformWindowsDefault();
                glfwMakeContextCurrent(backup_context);
            }
        }

    protected:
        window* local_window = nullptr;
    };
}


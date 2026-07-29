//
// Created by ellie on 7/28/26.
//

#include "imgui.h"
#include "../generalImports.h"
#include "../imgui_ext/imgui_perf_panel.h"
#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"

namespace Aura {
    class Renderer {
        public:

        bool Init(GLFWwindow* wind) {
            window = wind;

            IMGUI_CHECKVERSION();
            ImGui::CreateContext();
            ImGuiIO& io = ImGui::GetIO(); (void)io;
            io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
            ImGui::StyleColorsDark();

            ImGui_ImplGlfw_InitForOpenGL(window, true);
            ImGui_ImplOpenGL3_Init("#version 330");

            return true;
        }

        void BeginFrame() {
            ImGui_ImplOpenGL3_NewFrame();
            ImGui_ImplGlfw_NewFrame();

            ImGui::NewFrame();
            ImGui::DockSpaceOverViewport(0, nullptr, ImGuiDockNodeFlags_PassthruCentralNode);

            glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        }

        void EndFrame() {
            perfPanel->BeginPanel();
            ImGui::ShowDebugLogWindow();

            ImGui::Render();
            ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        }

        private:

        GLFWwindow* window = nullptr;

        PerformancePanel *perfPanel = new PerformancePanel();
    };
}

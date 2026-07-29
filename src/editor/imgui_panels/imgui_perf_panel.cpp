//
// Created by ellie on 7/29/26.
//

#include "imgui_perf_panel.h"

#include "imgui.h"
#include "GLFW/glfw3.h"

namespace AuraEditor {
    void PerformancePanel::BeginPanel() {
        ImGui::Begin("Aura Diag");
        ImGui::Text("FPS: %.1f", ImGui::GetIO().Framerate);

        if (ImGui::Checkbox("Enable VSync", &m_VSyncEnabled)) {
            glfwSwapInterval(m_VSyncEnabled ? 1:0);
        }
        ImGui::End();
    }
}

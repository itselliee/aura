//
// Created by ellie on 7/29/26.
//

#ifndef AURA_PANEL_LAYER_H
#define AURA_PANEL_LAYER_H
#include <iostream>

#include "imgui.h"
#include "layer.h"

class panel_layer : public aura::layer {
public:
    aura::window* m_window;

    panel_layer(aura::window *window) : layer("editor_panels") { m_window = window; }

    void on_attach() override {
        std::cout << "attached panel layer to engine layerstack" << std::endl;
    }

    void on_gui() override {
        static float lastUpdateTime = 0.0f;
        static float displayedFPS = 0.0f;
        static float displayedMsPerFrame = 0.0f;
        static bool vSync = false;

        static bool show_perf_window = true;

        float currentTime = ImGui::GetTime();

        if (currentTime - lastUpdateTime >= 1.0f)
        {
            displayedFPS = ImGui::GetIO().Framerate;

            if (displayedFPS > 0.0f) {
                displayedMsPerFrame = 1000.0f / displayedFPS;
            } else {
                displayedMsPerFrame = 0.0f;
            }

            lastUpdateTime = currentTime;
        }

        if (ImGui::BeginMainMenuBar()) {
            if (ImGui::BeginMenu("File")) {
                if (ImGui::MenuItem("Close")) {
                    glfwSetWindowShouldClose(m_window->glfw_window(), GLFW_TRUE);
                }
                ImGui::EndMenu();
            }

            if (ImGui::BeginMenu("Windows")) {
                if (ImGui::MenuItem("Performance & Settings")) {
                    show_perf_window = !show_perf_window;
                }
                ImGui::EndMenu();
            }
            ImGui::EndMainMenuBar();
        }

        if (show_perf_window) {
            ImGui::Begin("Performance Monitor & Settings");
            ImGui::Text("FPS: %.1f", displayedFPS);
            ImGui::Text("Frametime: %.3fms", displayedMsPerFrame);
            if (ImGui::Checkbox("VSync", &vSync)) {
                glfwSwapInterval(vSync ? 1 : 0);
            }
            ImGui::End();
        }

    }
};

#endif //AURA_PANEL_LAYER_H

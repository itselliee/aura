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
    panel_layer() : layer("editor_panels") {}

    void on_attach() override {
        std::cout << "attached to game" << std::endl;
    }

    void on_gui() override {
        static float lastUpdateTime = 0.0f;
        static float displayedFPS = 0.0f;
        static float displayedMsPerFrame = 0.0f;
        static bool vSync = false;

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

        ImGui::Begin("Performance Monitor & Settings");
        ImGui::Text("FPS: %.1f", displayedFPS);
        ImGui::Text("Frametime: %.3fms", displayedMsPerFrame);
        if (ImGui::Checkbox("VSync", &vSync)) {
            glfwSwapInterval(vSync ? 1 : 0);
        }
        ImGui::End();

    }
};

#endif //AURA_PANEL_LAYER_H

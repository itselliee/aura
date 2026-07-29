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
        ImGui::Begin("Test window");
        ImGui::End();
    }
};

#endif //AURA_PANEL_LAYER_H

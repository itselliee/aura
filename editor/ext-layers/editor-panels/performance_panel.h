//
// Created by ellie on 7/31/26.
//

#ifndef AURA_PERFORMANCE_PANEL_H
#define AURA_PERFORMANCE_PANEL_H
#include "imgui.h"
#include "layer_stack.h"

namespace aura_editor {
    class performance_panel : public aura_core::layer {
        void on_render() override {
            ImGui::Begin("test", nullptr, 0);
            ImGui::Text("This works!");
            ImGui::End();
        }
    };
} // aura_editor

#endif //AURA_PERFORMANCE_PANEL_H

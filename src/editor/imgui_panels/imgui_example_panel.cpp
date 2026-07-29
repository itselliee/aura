//
// Created by ellie on 7/29/26.
//

#include "imgui_example_panel.h"

#include "imgui.h"

namespace AuraEditor {
    void ExamplePanel::BeginPanel() {
        ImGui::Begin("Test panel", nullptr, 0);
        ImGui::Text("Hello from Test panel");
        ImGui::End();
    }
} // AuraEditor
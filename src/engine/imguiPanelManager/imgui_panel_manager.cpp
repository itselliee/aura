//
// Created by ellie on 7/29/26.
//

#include "imgui_panel_manager.h"

namespace Aura {
    AuraEditor::PerformancePanel *ImGuiPanelManager::perf_panel = new AuraEditor::PerformancePanel();
    AuraEditor::ExamplePanel *ImGuiPanelManager::example_panel = new AuraEditor::ExamplePanel();

    void ImGuiPanelManager::Panels() {
        perf_panel->BeginPanel();
        example_panel->BeginPanel();
        // put panels here
    }
} // Aura
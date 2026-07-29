//
// Created by ellie on 7/29/26.
//

#ifndef AURA_IMGUIPANELMANAGER_H
#define AURA_IMGUIPANELMANAGER_H
#include "../../editor/imgui_panels/imgui_example_panel.h"
#include "../../editor/imgui_panels/imgui_perf_panel.h"

namespace Aura {
    class ImGuiPanelManager {
    public:
        static void Panels();
    private:
        static AuraEditor::PerformancePanel *perf_panel;
        static AuraEditor::ExamplePanel *example_panel;
    };
} // Aura

#endif //AURA_IMGUIPANELMANAGER_H

//
// Created by ellie on 8/1/26.
//

#ifndef AURA_THEME_IMGUI_H
#define AURA_THEME_IMGUI_H
#include "imgui.h"

namespace aura_editor {
    class imgui_themes {
    public:
        static void apply_theme() {

            ImGuiStyle &style = ImGui::GetStyle();
            style.WindowRounding = 8.0f;
            style.TabRounding = 0.0f;
            style.WindowMenuButtonPosition = ImGuiDir_None;
            style.Colors[ImGuiCol_TitleBgActive] = ImVec4(0.690f, 0.525f, 0.796f, 1.000f);

            style.Colors[ImGuiCol_WindowBg] = ImVec4(0.090f, 0.080f, 0.100f, 1.000f);
            style.Colors[ImGuiCol_ChildBg] = ImVec4(0.110f, 0.100f, 0.130f, 1.000f);
            style.Colors[ImGuiCol_PopupBg] = ImVec4(0.120f, 0.110f, 0.140f, 1.000f);
            style.Colors[ImGuiCol_TitleBg] = ImVec4(0.140f, 0.120f, 0.160f, 1.000f);
            style.Colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.090f, 0.080f, 0.100f, 0.600f);

            style.Colors[ImGuiCol_Tab] = ImVec4(0.140f, 0.120f, 0.160f, 1.000f);
            style.Colors[ImGuiCol_TabHovered] = ImVec4(0.450f, 0.350f, 0.550f, 1.000f);
            style.Colors[ImGuiCol_TabActive] = ImVec4(0.250f, 0.200f, 0.300f, 1.000f);
            style.Colors[ImGuiCol_TabSelectedOverline] = ImVec4(0.690f, 0.525f, 0.796f, 1.000f);
            style.Colors[ImGuiCol_TabDimmed] = ImVec4(0.110f, 0.100f, 0.130f, 1.000f);
            style.Colors[ImGuiCol_TabDimmedSelected] = ImVec4(0.180f, 0.150f, 0.220f, 1.000f);
            style.Colors[ImGuiCol_TabDimmedSelectedOverline] = ImVec4(0.500f, 0.380f, 0.580f, 1.000f);


            style.Colors[ImGuiCol_CheckMark] = ImVec4(0.690f, 0.525f, 0.796f, 1.000f);
            style.Colors[ImGuiCol_SliderGrab] = ImVec4(0.500f, 0.380f, 0.580f, 1.000f);
            style.Colors[ImGuiCol_SliderGrabActive] = ImVec4(0.690f, 0.525f, 0.796f, 1.000f);

            style.Colors[ImGuiCol_FrameBg] = ImVec4(0.180f, 0.150f, 0.220f, 1.000f);
            style.Colors[ImGuiCol_FrameBgHovered] = ImVec4(0.250f, 0.200f, 0.300f, 1.000f);
            style.Colors[ImGuiCol_FrameBgActive] = ImVec4(0.350f, 0.280f, 0.420f, 1.000f);

            style.Colors[ImGuiCol_Button] = ImVec4(0.250f, 0.200f, 0.300f, 1.000f);
            style.Colors[ImGuiCol_ButtonHovered] = ImVec4(0.450f, 0.350f, 0.550f, 1.000f);
            style.Colors[ImGuiCol_ButtonActive] = ImVec4(0.690f, 0.525f, 0.796f, 1.000f);

            style.Colors[ImGuiCol_Header] = ImVec4(0.220f, 0.180f, 0.260f, 1.000f);
            style.Colors[ImGuiCol_HeaderHovered] = ImVec4(0.450f, 0.350f, 0.550f, 1.000f);
            style.Colors[ImGuiCol_HeaderActive] = ImVec4(0.690f, 0.525f, 0.796f, 1.000f);

            style.Colors[ImGuiCol_Text] = ImVec4(0.950f, 0.950f, 0.980f, 1.000f);
            style.Colors[ImGuiCol_TextDisabled] = ImVec4(0.500f, 0.480f, 0.550f, 1.000f);
            style.Colors[ImGuiCol_Border] = ImVec4(0.250f, 0.220f, 0.300f, 0.800f);
            style.Colors[ImGuiCol_Separator] = ImVec4(0.250f, 0.220f, 0.300f, 0.800f);
            style.Colors[ImGuiCol_ResizeGrip] = ImVec4(0.250f, 0.200f, 0.300f, 0.200f);
            style.Colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.450f, 0.350f, 0.550f, 0.600f);
            style.Colors[ImGuiCol_ResizeGripActive] = ImVec4(0.690f, 0.525f, 0.796f, 0.900f);

            style.Colors[ImGuiCol_DockingPreview] = ImVec4(0.690f, 0.525f, 0.796f, 0.700f);
            style.Colors[ImGuiCol_DockingEmptyBg] = ImVec4(0.090f, 0.080f, 0.100f, 1.000f);

            style.Colors[ImGuiCol_ScrollbarBg] = ImVec4(0.090f, 0.080f, 0.100f, 1.000f);
            style.Colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.250f, 0.200f, 0.300f, 1.000f);
            style.Colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.450f, 0.350f, 0.550f, 1.000f);
            style.Colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.690f, 0.525f, 0.796f, 1.000f);

            style.Colors[ImGuiCol_MenuBarBg] = ImVec4(0.140f, 0.120f, 0.160f, 1.000f);

            style.Colors[ImGuiCol_DragDropTarget] = ImVec4(0.690f, 0.525f, 0.796f, 0.900f);

            style.Colors[ImGuiCol_NavCursor] = ImVec4(0.690f, 0.525f, 0.796f, 1.000f);
            style.Colors[ImGuiCol_SeparatorHovered] = ImVec4(0.450f, 0.350f, 0.550f, 1.000f);
            style.Colors[ImGuiCol_SeparatorActive]  = ImVec4(0.690f, 0.525f, 0.796f, 1.000f);
        }
    };
}

#endif //AURA_THEME_IMGUI_H

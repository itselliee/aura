//
// Created by ellie on 7/29/26.
//

#include <iostream>
#include "layer.h"
#include "window.h"
#include "../../third-party/imgui/imgui.h"
#include "../../third-party/imgui/backends/imgui_impl_glfw.h"
#include "../../third-party/imgui/backends/imgui_impl_opengl3.h"

namespace aura {
    class render_pipeline : public layer {
    public:
        render_pipeline(window *window) : layer("render_pipeline") { local_window = window; }

        void on_attach() override {
            std::cout << "render pipeline running" << std::endl;
            IMGUI_CHECKVERSION();
            ImGui::CreateContext();
            ImGuiIO &io = ImGui::GetIO();
            io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
            ImGui::StyleColorsDark();
            ImGui::GetStyle().WindowRounding = 4.0f;

            ImGui_ImplGlfw_InitForOpenGL(local_window->glfw_window(), true);
            ImGui_ImplOpenGL3_Init("#version 330");
        }

        void apply_theme() {
            ImGuiStyle &style = ImGui::GetStyle();
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

        void on_detach() override {
            ImGui_ImplOpenGL3_Shutdown();
            ImGui_ImplGlfw_Shutdown();
            ImGui::DestroyContext();
        }

        void on_update(float deltaTime) override {
        }

        void on_render() override {
            ImGui_ImplOpenGL3_NewFrame();
            ImGui_ImplGlfw_NewFrame();
            apply_theme();
            ImGui::NewFrame();
            ImGui::DockSpaceOverViewport(0, nullptr, ImGuiDockNodeFlags_PassthruCentralNode);

            glClearColor(0.075f, 0.075f, 0.075f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        }

        void on_gui() override {
            ImGui::Render();
            ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

            // Required since you enabled ImGuiConfigFlags_ViewportsEnable
            ImGuiIO &io = ImGui::GetIO();
            if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable) {
                GLFWwindow *backup_context = glfwGetCurrentContext();
                ImGui::UpdatePlatformWindows();
                ImGui::RenderPlatformWindowsDefault();
                glfwMakeContextCurrent(backup_context);
            }
        }

    protected:
        window *local_window = nullptr;
    };
}

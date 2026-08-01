//
// Created by ellie on 7/31/26.
//

#ifndef AURA_PERFORMANCE_PANEL_H
#define AURA_PERFORMANCE_PANEL_H
#include "imgui.h"
#include "imspinner_compat.h"
#include "imspinner_shapes.h"
#include "layer_stack.h"
#include "../../utils/theme_imgui.h"

namespace aura_editor {
    class performance_panel : public aura_core::layer {
    public:
        performance_panel(aura_core::app* app) {
            m_app = app;
        }

        ImGuiIO& io = ImGui::GetIO();
        ImFont* font{};

        static inline bool vsync = false;

        static inline float displayedFPS = 0.0f;
        static inline float timer = 0.0f;

        void on_attach() override {
            font = io.Fonts->AddFontFromFileTTF("editor_res/fonts/sfpro-med.ttf", 16.0f, nullptr, io.Fonts->GetGlyphRangesDefault());
        }

        void pre_render() override {
            ImGui::PushFont(font);
            imgui_themes::apply_theme();
        }

        void on_render() override {
            float framerate = io.Framerate;

            //ImGui::ShowDebugLogWindow();

            perf_panel(framerate);
            menu_bar();

            ImGui::PopFont();
        }

    private:
        aura_core::app* m_app;

        void menu_bar() {
            if (ImGui::BeginMainMenuBar()) {
                if (ImGui::BeginMenu("File")) {
                    if (ImGui::MenuItem("Exit")) {
                        glfwSetWindowShouldClose(m_app->get_window()->get_window(), GLFW_TRUE);
                    }
                    ImGui::EndMenu();
                }
                ImGui::EndMainMenuBar();
            }
        }

        void perf_panel(float framerate) {
            ImGui::Begin("Performance Graph", nullptr, 0);

            timer += ImGui::GetIO().DeltaTime;
            if (timer >= 1.0f)
            {
                displayedFPS = framerate;
                timer = 0.0f;
            }

            ImGui::Text("FPS: %.2f", displayedFPS);

            if (ImGui::Checkbox("VSync", &vsync)) {
                glfwSwapInterval(vsync ? 1 : 0);
            }
            ImGui::End();
        }
    };
} // aura_editor

#endif //AURA_PERFORMANCE_PANEL_H

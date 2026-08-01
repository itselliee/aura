//
// Created by ellie on 7/31/26.
//

#ifndef AURA_PERFORMANCE_PANEL_H
#define AURA_PERFORMANCE_PANEL_H
#include "imgui.h"
#include "imspinner_compat.h"
#include "imspinner_shapes.h"
#include "layer_stack.h"
#include "../utils/theme_imgui.h"

namespace aura_editor {
    class panels : public aura_core::layer {
    public:
        panels(aura_core::app* app, aura_core::scene_renderer* renderer) {
            m_app = app;
            m_renderer = renderer;
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

            ImGui::ShowDebugLogWindow();

            viewport_panel();
            perf_panel(framerate);
            menu_bar();

            ImGui::PopFont();
        }

    private:
        aura_core::app* m_app;
        aura_core::scene_renderer* m_renderer;

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

        void viewport_panel() {
            ImGui::Begin("Viewport");

            ImVec2 panel_size = ImGui::GetContentRegionAvail();
            float target_aspect = 16.0f / 9.0f;
            float panel_aspect = panel_size.x / panel_size.y;

            ImVec2 image_size;
            if (panel_aspect > target_aspect) {
                image_size.y = panel_size.y;
                image_size.x = image_size.y * target_aspect;
            } else {
                image_size.x = panel_size.x;
                image_size.y = image_size.x / target_aspect;
            }

            ImVec2 cursor_pos = ImGui::GetCursorPos();
            ImGui::SetCursorPos(ImVec2(
                cursor_pos.x + (panel_size.x - image_size.x) * 0.5f,
                cursor_pos.y + (panel_size.y - image_size.y) * 0.5f
            ));

            GLuint tex_id = m_renderer->m_color_texture;
            ImGui::Image((ImTextureID)(intptr_t)tex_id, image_size, ImVec2(0, 1), ImVec2(1, 0));

            ImGui::End();
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

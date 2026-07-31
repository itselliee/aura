//
// Created by ellie on 7/29/26.
//
#ifndef AURA_PANEL_LAYER_H
#define AURA_PANEL_LAYER_H
#include <iostream>
#include "imgui.h"
#include "layer.h"
#include <stb_image.h>

class panel_layer : public aura::layer {
public:
    aura::window *m_window;

    // texture state
    GLuint m_logo_texture = 0;
    int m_logo_width = 0;
    int m_logo_height = 0;

    panel_layer(aura::window *window) : layer("editor_panels") { m_window = window; }

    GLuint LoadTextureFromFile(const char *filename, int *out_width, int *out_height) {
        int channels;
        unsigned char *data = stbi_load(filename, out_width, out_height, &channels, 4);
        if (data == NULL) return 0;

        GLuint texture_id;
        glGenTextures(1, &texture_id);
        glBindTexture(GL_TEXTURE_2D, texture_id);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, *out_width, *out_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        stbi_image_free(data);
        return texture_id;
    }

    void on_attach() override {
        std::cout << "attached panel layer to engine layerstack" << std::endl;

        m_logo_texture = LoadTextureFromFile("resources/logo.png", &m_logo_width, &m_logo_height);
        if (m_logo_texture == 0) {
            std::cout << "failed to load logo.png" << std::endl;
        }
    }

    void on_gui() override {
        static float lastUpdateTime = 0.0f;
        static float displayedFPS = 0.0f;
        static float displayedMsPerFrame = 0.0f;
        static bool vSync = false;
        static bool show_perf_window = true;
        static bool show_console_window = true;
        static bool open_about_popup = false;
        static float modal_alpha = 0.0f;
        const float fade_speed = 6.0f;

        float currentTime = ImGui::GetTime();
        if (currentTime - lastUpdateTime >= 1.0f) {
            displayedFPS = ImGui::GetIO().Framerate;
            displayedMsPerFrame = displayedFPS > 0.0f ? 1000.0f / displayedFPS : 0.0f;
            lastUpdateTime = currentTime;
        }

        if (ImGui::BeginMainMenuBar()) {
            if (ImGui::BeginMenu("File")) {
                if (ImGui::MenuItem("About")) {
                    open_about_popup = true;
                }
                ImGui::Separator();
                if (ImGui::MenuItem("Close")) {
                    glfwSetWindowShouldClose(m_window->glfw_window(), GLFW_TRUE);
                }
                ImGui::EndMenu();
            }
            if (ImGui::BeginMenu("Window")) {
                if (ImGui::MenuItem("Performance & Settings")) {
                    show_perf_window = !show_perf_window;
                }
                if (ImGui::MenuItem("Console")) {
                    show_console_window = !show_console_window;
                }
                ImGui::EndMenu();
            }
            ImGui::EndMainMenuBar();
        }

        if (open_about_popup) {
            ImGui::OpenPopup("About");
            modal_alpha = 0.0f;
            open_about_popup = false;
        }

        ImGuiWindowFlags flags = ImGuiWindowFlags_NoResize |
                                 ImGuiWindowFlags_NoMove |
                                 ImGuiWindowFlags_NoCollapse;

        if (ImGui::IsPopupOpen("About")) {
            modal_alpha += ImGui::GetIO().DeltaTime * fade_speed;
            if (modal_alpha > 1.0f) modal_alpha = 1.0f;

            ImGui::PushStyleVar(ImGuiStyleVar_Alpha, modal_alpha);
            ImGui::PushStyleColor(ImGuiCol_ModalWindowDimBg, ImVec4(0.05f, 0.05f, 0.05f, 0.65f * modal_alpha));

            ImGuiViewport *viewport = ImGui::GetMainViewport();
            ImVec2 center_pos(viewport->Pos.x + viewport->Size.x * 0.5f, viewport->Pos.y + viewport->Size.y * 0.5f);
            ImGui::SetNextWindowPos(center_pos, ImGuiCond_Always, ImVec2(0.5f, 0.5f));
            ImGui::SetNextWindowSize(ImVec2(260.0f, 320.0f), ImGuiCond_Always);

            if (ImGui::BeginPopupModal("About", nullptr, flags)) {
                if (m_logo_texture != 0) {
                    float display_w = 96.0f;
                    float display_h = display_w * (float) m_logo_height / (float) m_logo_width;
                    float avail_w = ImGui::GetContentRegionAvail().x;
                    ImGui::SetCursorPosX((avail_w - display_w) * 0.5f + ImGui::GetCursorPosX());
                    ImGui::Image((ImTextureID) (intptr_t) m_logo_texture, ImVec2(display_w, display_h));
                    ImGui::Spacing();
                }
                ImGui::Text("aURA Editor 0.0.0.1  < main branch");
                ImGui::Separator();
                ImGui::Text("Made with <3 by Ellie");
                ImGui::Text("\nWe use OpenGL, Dear ImGui and GLFW\nto make this possible!");
                ImGui::Spacing();

                ImVec2 button_size(120.0f, ImGui::GetFrameHeight());
                float margin = 12.0f;
                ImVec2 content_max = ImGui::GetContentRegionMax();
                ImVec2 target_pos(margin, content_max.y - button_size.y - margin);
                ImGui::SetCursorPos(target_pos);
                if (ImGui::Button("OK", button_size)) {
                    ImGui::CloseCurrentPopup();
                }

                ImGui::EndPopup();
            }

            ImGui::PopStyleColor();
            ImGui::PopStyleVar();
        }

        if (show_perf_window) {
            ImGui::Begin("Performance Monitor & Settings");
            ImGui::Text("FPS: %.1f", displayedFPS);
            ImGui::Text("Frametime: %.3fms", displayedMsPerFrame);
            if (ImGui::Checkbox("VSync", &vSync)) {
                glfwSwapInterval(vSync ? 1 : 0);
            }
            ImGui::End();
        }

        if (show_console_window) {
            ImGui::ShowDebugLogWindow();
        }
    }
};
#endif //AURA_PANEL_LAYER_H

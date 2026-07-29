//
// Created by ellie on 7/29/26.
//

#include "render.h"

#include "../../editor/imgui_panels/imgui_example_panel.h"
#include "../../editor/imgui_panels/imgui_perf_panel.h"
#include "../imguiPanelManager/imgui_panel_manager.h"
#include "backends/imgui_impl_opengl3_loader.h"
#include "../shader/shader_compilation_handler.h"

namespace Aura {
    static float vertices[] = {
         0.5f,  0.5f, 0.0f,
         0.5f, -0.5f, 0.0f,
        -0.5f, -0.5f, 0.0f,
        -0.5f,  0.5f, 0.0f
    };

    static int indicies[] = {
        0, 1, 3,
        1, 2, 3
    };

    GLuint basicProgram;

    unsigned int VBO, VAO, EBO;

    bool Renderer::Init(GLFWwindow* wind) {
        window = wind;

        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGuiIO& io = ImGui::GetIO(); (void)io;
        io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
        ImGui::StyleColorsDark();

        ImGui_ImplGlfw_InitForOpenGL(window, true);
        ImGui_ImplOpenGL3_Init("#version 330");

        //shader reading time
        auto programs = ShaderCompilationHandler::LoadShadersFromFolder("shaders/");
        basicProgram = programs["basic"];

        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);
        glGenBuffers(1, &EBO);

        glBindVertexArray(VAO);

        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indicies), indicies, GL_STATIC_DRAW);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);

        glBindBuffer(GL_ARRAY_BUFFER, 0);

        glBindVertexArray(0);

        return true;
    }

    void Renderer::BeginFrame() {
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();

        ImGui::NewFrame();
        ImGui::DockSpaceOverViewport(0, nullptr, ImGuiDockNodeFlags_PassthruCentralNode);

        glClearColor(0.075f, 0.075f, 0.075f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }

    void Renderer::OglRenderPass() {

        glUseProgram(basicProgram);
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);

    }

    void Renderer::EndFrame() {
        ImGuiPanelManager::Panels();

        ImGui::ShowDebugLogWindow();

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    }
}

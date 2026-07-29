//
// Created by ellie on 7/28/26.
//

#include <functional>

#include <glad/glad.h>
#include "GLFW/glfw3.h"

#include "imgui.h"
#include "../../editor/imgui_panels/imgui_example_panel.h"
#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"

namespace Aura {
    class Renderer {
        public:

        bool Init(GLFWwindow* wind);

        static void BeginFrame();

        static void OglRenderPass();

        static void EndFrame();

        private:

        GLFWwindow* window = nullptr;


    };
}

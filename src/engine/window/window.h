//
// Created by ellie on 7/28/26.
//
#pragma once

#include "../generalImports.h"
#include "../input/inputsys.h"

namespace Aura {
    class Window {
        public:

        GLFWwindow* window = nullptr;
        int CURRENT_WIDTH = 0, CURRENT_HEIGHT = 0;

        ~Window();

        bool createWindow(int width, int height);

        [[nodiscard]] bool ShouldClose() const;

        static void PollEvents();

        void SwapBuffers() const;

        private:

        static void frameBufferSizeCallback(GLFWwindow* window, int width, int height) {
            glViewport(0, 0, width, height);
        }

        static void glfw_key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
            InputSystem::pushEvent(key, action, mods);
        }
    };
}

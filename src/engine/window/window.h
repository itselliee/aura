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

        bool createWindow(int width, int height) {
            std::cout << "Initializing window" << std::endl;

            glfwInit();
            glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
            glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
            glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

            CURRENT_WIDTH = width;
            CURRENT_HEIGHT = height;

            window = glfwCreateWindow(width, height, "Aura", nullptr, nullptr);

            InputSystem::eventQueue.reserve(64);

            if (window == nullptr) {
                std::cerr << "Whoops! Aura encountered and error and has to exit. Error code: glass" << std::endl;
                glfwTerminate();
                return false;
            }

            glfwMakeContextCurrent(window);

            if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
                std::cerr << "Whoops! Aura encountered and error and has to exit. Error code: glad" << std::endl;
                return false;
            }

            glViewport(0, 0, CURRENT_WIDTH, CURRENT_HEIGHT);

            glfwSetKeyCallback(window, glfw_key_callback);
            glfwSetFramebufferSizeCallback(window, frameBufferSizeCallback);

            return true;
        }

        bool ShouldClose() const {
            return glfwWindowShouldClose(window);
        }

        void PollEvents() const {
            glfwPollEvents();
        }

        void SwapBuffers() const {
            glfwSwapBuffers(window);
        }

        ~Window() {
            std::cout << "Destroying window" << std::endl;
            if (window) glfwDestroyWindow(window);
            glfwTerminate();
        }

        private:

        static void frameBufferSizeCallback(GLFWwindow* window, int width, int height) {
            glViewport(0, 0, width, height);
        }

        static void glfw_key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
            InputSystem::pushEvent(key, action, mods);
        }

    };
}

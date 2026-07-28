//
// Created by ellie on 7/28/26.
//

#ifndef AURA_IWINDOW_H
#define AURA_IWINDOW_H

#include <functional>
#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace Aura {
    class IWindow {
    public:
        GLFWwindow* window; // need this so the mainloop of the application can run proper polls through it

        int CURRENT_WIDTH, CURRENT_HEIGHT;

        void Initialize(int width, int height, std::function<void()> renderCallback) {
            std::cout << "Initializing window via GLFW" << std::endl;

            glfwInit();
            glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
            glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
            glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

            CURRENT_HEIGHT = height;
            CURRENT_WIDTH = width;

            window = glfwCreateWindow(CURRENT_WIDTH, CURRENT_HEIGHT, "Aura", nullptr, nullptr);

            if (window == nullptr) {
                std::cout << "Failed to create GLFW window" << std::endl;
                glfwTerminate();
                return;
            }

            glfwMakeContextCurrent(window);

            if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
                std::cout << "Failed to initialize GLAD" << std::endl;
                return;
            }

            glViewport(0, 0, CURRENT_WIDTH, CURRENT_HEIGHT);

            glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

            while (!glfwWindowShouldClose(window)) {
                WindowInputEscape();

                if (renderCallback != nullptr) {
                    renderCallback();
                }

                glfwSwapBuffers(window);
                glfwPollEvents();
            }
        }

        ~IWindow() {
            std::cout << "De-initializing GLFW.." << std::endl;

            glfwDestroyWindow(window);
            glfwTerminate();

            // Finally let Application let go of GLFW window!
        }

        void WindowInputEscape() {
            if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
                std::cout << "Escape key pressed" << std::endl;
                glfwSetWindowShouldClose(window, GLFW_TRUE);
            }
        }

    private:

        static void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
            glViewport(0, 0, width, height);
        }
    };
}


#endif //AURA_IWINDOW_H

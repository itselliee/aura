//
// Created by ellie on 7/31/26.
//

#include "window.h"

#include <iostream>
#include <ostream>

namespace aura_core {
    window::window(int width, int height) {
        std::cout << "window: creating window" << std::endl;

        glfwInit();
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#if IS_APPLE_PLATFORM
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

        glfw_window = glfwCreateWindow(width, height, "aURA", nullptr, nullptr);

        if (glfw_window == nullptr) {
            std::cerr << "window: failed to create GLFW window, aborting" << std::endl;
            glfwTerminate();
            return;
        }

        glfwMakeContextCurrent(glfw_window);

        if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
            std::cerr << "window: glad init failed, aborting" << std::endl;
            return;
        }

        glfwSetFramebufferSizeCallback(glfw_window, framebuffer_size_callback);
        glfwSwapInterval(0);

        std::cout << "window: initialized successfully" << std::endl;

        return;
    }

    window::~window() {
        std::cout << "window: destroying window" << std::endl;
        if (glfw_window) glfwDestroyWindow(glfw_window);
        glfwTerminate();
    }

    void window::refresh() const {
        glfwPollEvents();
        glfwSwapBuffers(glfw_window);
    }

    bool window::should_close() const {
        return glfwWindowShouldClose(glfw_window);
    }

    GLFWwindow* window::get_window() const {
        return glfw_window;
    }

    void window::framebuffer_size_callback(GLFWwindow* window, int width, int height) {
        glViewport(0, 0, width, height);
    }
}

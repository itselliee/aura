//
// Created by ellie on 7/29/26.
//

#include "window.h"

namespace Aura {
    bool Window::createWindow(const int width, const int height) {
        std::cout << "Initializing window" << std::endl;

        glfwInit();
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#if IS_APPLE_PLATFORM
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

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

        glfwSwapInterval(0);

        return true;
    }

    bool Window::ShouldClose() const {
        return glfwWindowShouldClose(window);
    }

    void Window::PollEvents() {
        glfwPollEvents();
    }

    void Window::SwapBuffers() const {
        glfwSwapBuffers(window);
    }

    Window::~Window() {
        std::cout << "Destroying window" << std::endl;
        if (window) glfwDestroyWindow(window);
        glfwTerminate();
    }
}

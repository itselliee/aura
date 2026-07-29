//
// Created by ellie on 7/29/26.
//

#include "window.h"

namespace aura {
    window::window(const int width, const int height) {
        std::cout << "Initializing window" << std::endl;

        glfwInit();
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#if IS_APPLE_PLATFORM
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GLFW_TRUE);
#endif

        m_window = glfwCreateWindow(width, height, "aURA", nullptr, nullptr);

        if (m_window == nullptr) {
            std::cerr << "Failed to create GLFW window" << std::endl;
            glfwTerminate();
            return;
        }

        glfwMakeContextCurrent(m_window);

        if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
            std::cerr << "Failed to initialize GLAD" << std::endl;
            return;
        }

        glfwSetFramebufferSizeCallback(m_window, frame_buffer_size_callback);

        glfwSwapInterval(0);

        return;
    }

    window::~window() {
        std::cout << "Destroying window" << std::endl;
        if (m_window) glfwDestroyWindow(m_window);
        glfwTerminate();
    }

    bool window::should_close() const {
        return glfwWindowShouldClose(m_window);
    }

    void window::window_refresh() const {
        glfwPollEvents();
        glfwSwapBuffers(m_window);
    }
}

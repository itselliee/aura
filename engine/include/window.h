//
// Created by ellie on 7/31/26.
//

#ifndef AURA_WINDOW_H
#define AURA_WINDOW_H
#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace aura_core {
    class window {
    public:
        window(int width, int height);
        virtual ~window();

        void refresh() const;
        bool should_close() const;

        GLFWwindow *get_window() const;
    private:
        GLFWwindow* glfw_window = nullptr;

        static void framebuffer_size_callback(GLFWwindow* window, int width, int height);
    };
}

#endif //AURA_WINDOW_H

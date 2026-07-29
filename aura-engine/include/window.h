//
// Created by ellie on 7/29/26.
//
#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

namespace aura {
    class window {
    public:
        window(int width, int height);
        virtual ~window();

        ///<summary>
        /// BY ALL MEANS
        /// KEEP THIS RUNNING!!
        ///</summary>
        void window_refresh() const;
        bool should_close() const;

        GLFWwindow* glfw_window() {
            return m_window;
        }
    protected:
        GLFWwindow* m_window = nullptr;

        static void frame_buffer_size_callback(GLFWwindow* window, int width, int height) {
            glViewport(0, 0, width, height);
        }
    };
}


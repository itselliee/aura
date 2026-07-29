//
// Created by ellie on 7/29/26.
//
#pragma once
#include "imgui.h"
#include "GLFW/glfw3.h"

namespace Aura {
    class PerformancePanel {
    public:
        void BeginPanel();
    private:
        GLFWwindow* m_Window = nullptr;

        bool m_VSyncEnabled = false;
    };
}


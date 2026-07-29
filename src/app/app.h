//
// Created by ellie on 7/28/26.
//

#ifndef AURA_APP_H
#define AURA_APP_H
#include "../engine/input/input2text.h"
#include "../engine/render/render.h"
#include "../engine/window/window.h"

namespace Aura {
    std::vector<InputEvent> InputSystem::eventQueue;
    class App {
        public:

        void Run() {
            if (!m_Window->createWindow(1280, 720)) {
                std::cerr << "Failed to create window" << std::endl;
                return;
            }

            while (!m_Window->ShouldClose()) {
                m_Renderer->Render();

                for (const auto& event : InputSystem::eventQueue) {
                    std::string keyName = Input2Text::getCleanKeyName(event.keyId);

                    std::string actionName = (event.action == GLFW_PRESS)   ? "PRESSED"  :
                                             (event.action == GLFW_RELEASE) ? "RELEASED" : "HELD";

                    std::cout << "Input System: " << keyName << " was " << actionName << "\n";

                    if (keyName == "ESCAPE" && event.action == GLFW_PRESS) {
                        glfwSetWindowShouldClose(m_Window->window, GLFW_TRUE);
                    }
                }

                InputSystem::clearQueue();

                m_Window->SwapBuffers();
                m_Window->PollEvents();
            }
        }

        private:

        Window *m_Window = new Window();
        Renderer *m_Renderer = new Renderer();
    };
}

#endif //AURA_APP_H

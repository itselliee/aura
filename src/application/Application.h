//
// Created by ellie on 7/28/26.
//

#ifndef AURA_APPLICATION_H
#define AURA_APPLICATION_H
#include "../render/Renderer.h"
#include "../window/IWindow.h"

namespace Aura {
    class Application {
    public:
        Application() = default;
        ~Application() = default;

        void Run() {
            m_Window.Initialize(1280, 720, [this]() {
                m_Renderer.RenderStack();
            });
        }
    private:
        IWindow m_Window;
        Renderer m_Renderer;
    };
}


#endif //AURA_APPLICATION_H

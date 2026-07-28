//
// Created by ellie on 7/28/26.
//

#ifndef AURA_RENDERER_H
#define AURA_RENDERER_H
#include <iostream>

namespace Aura {
    class Renderer {
    public:
        Renderer() = default;
        ~Renderer() = default;

        void RenderStack() {
            glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT);
        }
    private:
    };
} // Aura

#endif //AURA_RENDERER_H

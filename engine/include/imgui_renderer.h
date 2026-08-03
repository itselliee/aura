//
// Created by Ellie on 03/08/2026.
//

#ifndef AURA_IMGUI_RENDERER_H
#define AURA_IMGUI_RENDERER_H

//
// Created by ellie on 7/31/26.
//

#include <iostream>
#include <ostream>

#include "../include/internal_layer_stack.h"

#include "backends/imgui_impl_sdl3.h"
#include "backends/imgui_impl_opengl3.h"

namespace aura_core {
    class imgui_renderer : public internal_layer {
    public:
        imgui_renderer(window *window) {
            m_window = window;
        }

        void on_attach() override;

        void gl_render_stg() override;

        void imgui_render_stg() override;

        void post_render() override;

        void on_detach() override;
    private:
        window * m_window;
    };
}


#endif //AURA_IMGUI_RENDERER_H

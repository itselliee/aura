//
// Created by Ellie on 03/08/2026.
//

#ifndef AURA_SCENE_RENDERER_H
#define AURA_SCENE_RENDERER_H

//
// Created by ellie on 8/1/26.
//

#include <iostream>
#include <ostream>

#include "internal_layer_stack.h"
#include <SDL3/SDL.h>

namespace aura_core {
    class scene_renderer : public internal_layer {
    public:
        scene_renderer() = default;
        ~scene_renderer() = default;

        const int width = 1920;
        const int height = 1080;

        GLuint m_framebuffer = 0;
        GLuint m_color_texture = 0;
        GLuint m_depth_rbo = 0;

        GLuint vbo = 0;

        // temp
        static inline float vertices[] = {
            -0.5f, -0.5f, 0.0f,
            0.5f, -0.5f, 0.0f,
            0.5f, 0.5f, 0.0f,
        };

        void on_attach() override;

        void create_framebuffer();

        void gl_render_stg() override;

        void on_detach() override;

    private:
        void cleanup_opengl();
    };
}


#endif //AURA_SCENE_RENDERER_H

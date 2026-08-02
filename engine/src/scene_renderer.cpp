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
        scene_renderer() {}

        ~scene_renderer() {
            cleanup_opengl();
        }

        const int width = 1920;
        const int height = 1080;

        GLuint m_framebuffer = 0;
        GLuint m_color_texture = 0;
        GLuint m_depth_rbo = 0;

        GLuint vbo;

        // temp
        static inline float vertices[] = {
            -0.5f, -0.5f, 0.0f,
            0.5f, -0.5f, 0.0f,
            0.5f,  0.5f, 0.0f,
        };

        void on_attach() override {
            create_framebuffer();
            std::cout << "ogl_render: initialized successfully" << std::endl;
        }

        void create_framebuffer() {
            glGenFramebuffers(1, &m_framebuffer);
            glBindFramebuffer(GL_FRAMEBUFFER, m_framebuffer);

            glGenTextures(1, &m_color_texture);
            glBindTexture(GL_TEXTURE_2D, m_color_texture);
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, nullptr);

            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
            glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, m_color_texture, 0);

            glGenRenderbuffers(1, &m_depth_rbo);
            glBindRenderbuffer(GL_RENDERBUFFER, m_depth_rbo);
            glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, width, height);
            glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, m_depth_rbo);

            if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
                std::cout << "ogl_render: framebuffer is not complete!" << std::endl;
            }

            glBindRenderbuffer(GL_RENDERBUFFER, 0);
            glBindFramebuffer(GL_FRAMEBUFFER, 0);
        }

        void gl_render_stg() override {
            glBindFramebuffer(GL_FRAMEBUFFER, m_framebuffer);
            glViewport(0, 0, width, height);

            glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

            // render here ellie
            glGenBuffers(1, &vbo);
            glBindBuffer(GL_ARRAY_BUFFER, vbo);
            glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

            glBindFramebuffer(GL_FRAMEBUFFER, 0);
        }

        void on_detach() override {
            cleanup_opengl();
        }

    private:
        void cleanup_opengl() {

            if (SDL_GL_GetCurrentContext() == nullptr) {
                std::cout << "CRITICAL WARN: Context already destroyed! Skipping glDelete calls to avoid SIGSEGV." << std::endl;
                return;
            }
            if (m_framebuffer != 0) {
                glDeleteFramebuffers(1, &m_framebuffer);
                m_framebuffer = 0;
            }
            if (m_color_texture != 0) {
                glDeleteTextures(1, &m_color_texture);
                m_color_texture = 0;
            }
            if (m_depth_rbo != 0) {
                glDeleteRenderbuffers(1, &m_depth_rbo);
                m_depth_rbo = 0;
            }
        }
    };
}

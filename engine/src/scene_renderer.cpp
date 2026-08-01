//
// Created by ellie on 8/1/26.
//

#include <iostream>
#include <ostream>

#include "internal_layer_stack.h"

namespace aura_core {
    class scene_renderer : public internal_layer {
    public:
        scene_renderer() {}
        ~scene_renderer() {}

        const int width = 1920; // for viewport fbo
        const int height = 1080; // for viewport fbo

        GLuint m_framebuffer = 0;
        GLuint m_color_texture;
        GLuint m_depth_rbo;

        void on_attach() override {
            create_framebuffer();
            std::cout << "ogl_render: intiialized successfully" << std::endl;
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

            glBindFramebuffer(GL_FRAMEBUFFER, 0);
        }
    };
}

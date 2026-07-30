//
// Created by ellie on 7/29/26.
//

#include "../include/application.h"
#include "render_pipeline.h"
#include "window.h"

namespace aura {

    application::application() {
        m_window = new window(1280, 720);
    }

    application::~application() {
        delete m_window;
    }

    void application::run() {
        while (!m_window->should_close() && m_running) {
            for (layer* layer : m_layer_stack) {
                layer->on_update(0);
            }

            for (layer* layer : m_layer_stack) {
                layer->on_render();
            }

            for (layer* layer : m_layer_stack) {
                if (layer->get_name() != "render_pipeline") {
                    layer->on_gui();
                }
            }

            if (!m_layer_stack.empty()) {
                m_layer_stack.front()->on_gui();
            }

            m_window->window_refresh();
        }
    }

    void application::push_layer(layer *layer) {
        m_layer_stack.push_layer(layer);

        if (m_window) {
            glfwMakeContextCurrent(m_window->glfw_window());
        }

        layer->on_attach();
    }

    aura::window * application::get_window() const {
        return m_window;
    }
} // aura

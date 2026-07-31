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
            // 1. Update Phase
            for (layer* layer : m_layer_stack) {
                layer->on_update(0);
            }

            // 2. Hardware Render Phase
            for (layer* layer : m_layer_stack) {
                layer->on_render();
            }

            // 3. Find our core render pipeline layer
            render_pipeline* pipeline = nullptr;
            for (layer* layer : m_layer_stack) {
                if (layer->get_name() == "render_pipeline") {
                    pipeline = static_cast<render_pipeline*>(layer);
                    break;
                }
            }

            // 4. GUI Lifecycle Phase
            if (pipeline) {
                pipeline->begin_gui(); // Starts ImGui frame & Dockspace safely
            }

            // Regular layers can now freely submit ImGui windows!
            for (layer* layer : m_layer_stack) {
                if (layer != pipeline) {
                    layer->on_gui();
                }
            }

            if (pipeline) {
                pipeline->on_gui();  // Render pipeline's own UI elements
                pipeline->end_gui(); // Finalises frame, renders, handles Viewports
            }

            // 5. Swap buffers
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

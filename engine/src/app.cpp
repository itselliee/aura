//
// Created by ellie on 7/31/26.
//

#include "app.h"

namespace aura_core {
    app::app() {
        m_window = new window(1280, 720);
        m_layerstack = new layer_stack();
        m_internal_layerstack = new internal_layer_stack();

        auto *renderer = new aura_core::renderer(m_window);
        // Here, put the internal layer stack objects you require to be implemented.
        m_internal_layerstack->push_layer(renderer);
    }
    app::~app() {
        delete m_window;
        delete m_internal_layerstack;
        delete m_layerstack;
    }

    void app::run() {
        while (!m_window->should_close() && m_app_running) {
            for (internal_layer* layer : *m_internal_layerstack) {
                layer->on_update(1);
            }

            for (internal_layer* layer : *m_internal_layerstack) {
                layer->pre_render();
            }

            for (internal_layer* layer : *m_internal_layerstack) {
                layer->gl_render_stg();
            }

            for (internal_layer* layer : *m_internal_layerstack) {
                layer->imgui_render_stg();
            }

            for (layer* layer : *m_layerstack) {
                layer->on_render();
            }

            for (internal_layer* layer : *m_internal_layerstack) {
                layer->post_render();
            }

            m_window->refresh();
        }
    }

    void app::push_layer(layer* layer) const {
        m_layerstack->push_layer(layer);
    }

    window *app::get_window() const { return m_window; }

    // private
}

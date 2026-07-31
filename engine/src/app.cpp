//
// Created by ellie on 7/31/26.
//

#include "app.h"

namespace aura_core {
    app::app() {
        m_layerstack = new layer_stack();
        m_internal_layerstack = new internal_layer_stack();

        // Here, put the internal layer stack objects you require to be implemented.   
    }
    app::~app() {
        delete m_window;
        delete m_internal_layerstack;
        delete m_layerstack;
    }

    void app::run() {

    }
    void app::push_layer(layer* layer) {
        m_layerstack->push_layer(layer);
    }

    int *app::get_window() const {

    }

    // private
}

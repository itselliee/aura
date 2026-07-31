//
// Created by ellie on 7/31/26.
//

#include "layer_stack.h"

namespace aura_core {
    layer_stack::~layer_stack() {
        for (layer* layer : m_layers) {
            layer->on_detach();
            delete layer;
        }
    }

    void layer_stack::push_layer(layer* layer) {
        m_layers.push_back(layer);
        layer->on_attach();
    }

    bool layer_stack::empty() const { return m_layers.empty(); }
    layer* layer_stack::front() const { return m_layers.front(); }
}

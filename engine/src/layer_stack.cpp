//
// Created by ellie on 7/31/26.
//

#include "layer_stack.h"

namespace aura_core {
    layer_stack::~layer_stack() {
        for (auto it = m_layers.rbegin(); it != m_layers.rend(); ++it) {
            (*it)->on_detach();
            delete *it;
        }
        m_layers.clear();
    }

    void layer_stack::push_layer(layer* layer) {
        m_layers.push_back(layer);
        layer->on_attach();
    }

    bool layer_stack::empty() const { return m_layers.empty(); }
    layer* layer_stack::front() const { return m_layers.front(); }
}

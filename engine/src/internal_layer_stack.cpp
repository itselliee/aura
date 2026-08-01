//
// Created by ellie on 7/31/26.
//

#include "internal_layer_stack.h"

namespace aura_core {
    internal_layer_stack::~internal_layer_stack() {
        for (auto it = m_layers.rbegin(); it != m_layers.rend(); ++it) {
            (*it)->on_detach();
            delete *it;
        }
        m_layers.clear();
    }

    void internal_layer_stack::push_layer(internal_layer* layer) {
        m_layers.push_back(layer);
        layer->on_attach();
    }

    bool internal_layer_stack::empty() const { return m_layers.empty(); }
    internal_layer* internal_layer_stack::front() const { return m_layers.front(); }
}

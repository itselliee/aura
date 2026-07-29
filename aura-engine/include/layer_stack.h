//
// Created by ellie on 7/29/26.
//

#ifndef AURA_LAYER_STACK_H
#define AURA_LAYER_STACK_H
#include <vector>
#include "layer.h"

namespace aura {
    class layer_stack {
    public:
        layer_stack() = default;
        ~layer_stack() {
            for (layer* layer : m_Layers) {
                layer->on_detach();
                delete layer;
            }
        }

        void push_layer(layer* layer) {
            m_Layers.emplace_back(layer);
        }

        bool empty() const { return m_Layers.empty(); }
        layer* front() { return m_Layers.front(); }


        std::vector<layer*>::iterator begin() { return m_Layers.begin(); }
        std::vector<layer*>::iterator end() { return m_Layers.end(); }
    private:
        std::vector<layer*> m_Layers;
    };
}

#endif //AURA_LAYER_STACK_H

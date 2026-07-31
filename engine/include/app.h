//
// Created by ellie on 7/31/26.
//

#ifndef AURA_APP_H
#define AURA_APP_H
#include "internal_layer_stack.h"
#include "layer_stack.h"
#include "window.h"
#include "../src/renderer.cpp"

namespace aura_core {
    class app {
    public:
        app();
        ~app();

        void run();

        void push_layer(layer* layer) const;

        [[nodiscard]] window* get_window() const;
    private:
        window *m_window = nullptr;
        layer_stack *m_layerstack;
        internal_layer_stack *m_internal_layerstack;
        bool m_app_running = true;
    };
}

#endif //AURA_APP_H

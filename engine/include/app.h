//
// Created by ellie on 7/31/26.
//

#ifndef AURA_APP_H
#define AURA_APP_H
#include "internal_layer_stack.h"
#include "layer_stack.h"

namespace aura_core {
    class app {
    public:
        app();
        ~app();

        void run();

        // TODO: FINISH THIS FUNCTIONS - AFTER window.h HAS BEEN MADE
        void push_layer(layer* layer);

        int* get_window() const;
    private:
        int *m_window = nullptr; // TODO
        layer_stack *m_layerstack; // TODO
        internal_layer_stack *m_internal_layerstack; // TODO
        bool m_app_running = true;
    };
}

#endif //AURA_APP_H

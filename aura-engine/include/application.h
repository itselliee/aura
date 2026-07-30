#pragma once
#include "layer_stack.h"
#include "window.h"

namespace aura {
    class application {
    public:
        application();
        ~application();

        void run();
        void push_layer(layer* layer);

        aura::window * get_window() const;

    private:
        window* m_window = nullptr;
        layer_stack m_layer_stack;
        bool m_running = true;
    };
}

//
// Created by ellie on 7/31/26.
//

#ifndef AURA_INTERNAL_LAYER_STACK_H
#define AURA_INTERNAL_LAYER_STACK_H
#include <string>
#include <vector>

#include "window.h"

namespace aura_core {
    class internal_layer {
    public:
        internal_layer(std::string name = "name_not_impl_internal") : m_debug_name(std::move(name)) {}

        explicit internal_layer(window * window);

        virtual ~internal_layer() = default;

        virtual void on_attach() {}
        virtual void on_detach() {}
        virtual void on_update(float deltaTime) {}
        virtual void pre_render() {}
        virtual void gl_render_stg() {}
        virtual void imgui_render_stg() {}
        virtual void post_render() {}

        const std::string &get_debug_name() const { return m_debug_name; }
    private:
        std::string m_debug_name;
    };

    class internal_layer_stack {
    public:
        internal_layer_stack() = default;
        ~internal_layer_stack();

        void push_layer(internal_layer* layer);

        bool empty() const;
        internal_layer* front() const;

        std::vector<internal_layer*>::iterator begin() { return m_layers.begin(); }
        std::vector<internal_layer*>::iterator end() { return m_layers.end(); }
    private:
        std::vector<internal_layer*> m_layers;
    };
}

#endif //AURA_INTERNAL_LAYER_STACK_H

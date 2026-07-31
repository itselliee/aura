//
// Created by ellie on 7/31/26.
//

#ifndef AURA_LAYER_STACK_H
#define AURA_LAYER_STACK_H
#include <string>
#include <vector>

namespace aura_core {
    class layer {
    public:
        layer(std::string name = "name_not_impl_internal") : m_debug_name(std::move(name)) {}
        virtual ~layer() = default;

        virtual void on_attach() {}
        virtual void on_detach() {}
        virtual void on_update(float deltaTime) {}
        virtual void pre_render() {}
        virtual void on_render() {}
        virtual void post_render() {}

        const std::string &get_debug_name() const { return m_debug_name; }
    private:
        std::string m_debug_name;
    };

    class layer_stack {
    public:
        layer_stack() = default;
        ~layer_stack();

        void push_layer(layer* layer);

        bool empty() const;
        layer* front() const;

        std::vector<layer*>::iterator begin() { return m_layers.begin(); }
        std::vector<layer*>::iterator end() { return m_layers.end(); }
    private:
        std::vector<layer*> m_layers;
    };
}


#endif //AURA_LAYER_STACK_H

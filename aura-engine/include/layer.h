//
// Created by ellie on 7/29/26.
//

#ifndef AURA_LAYER_H
#define AURA_LAYER_H

#pragma once
#include <string>
#include <utility>

namespace aura {
    class layer {
    public:
        layer(std::string  name = "Layer") : m_DebugName(std::move(name)) {}
        virtual ~layer() = default;

        virtual void on_attach() {}
        virtual void on_detach() {}
        virtual void on_update(float deltaTime) {}
        virtual void on_gui() {}
        virtual void on_render() {}

        const std::string& get_name() const { return m_DebugName; }
    protected:
        std::string m_DebugName;
    };
}

#endif //AURA_LAYER_H

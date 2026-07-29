//
// Created by ellie on 7/28/26.
//

#pragma once

#include "../generalImports.h"

namespace Aura {
    struct InputEvent {
        int keyId;
        int action;
        int modifiers;
    };

    class InputSystem {
    public:
        static std::vector<InputEvent> eventQueue;

        static void pushEvent(int key, int action, int mods) {
            if (key == GLFW_KEY_UNKNOWN) {
                return;
            }

            eventQueue.push_back({key, action, mods});
        }

        static void clearQueue() {
            eventQueue.clear();
        }
    };
}
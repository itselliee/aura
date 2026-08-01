//
// Created by ellie on 7/31/26.
//

#ifndef AURA_UTILITY_H
#define AURA_UTILITY_H

namespace aura_core {
    class utility {
    public:
        static inline float deltaTime = 0.0f;
        static inline float lastFrameTime = 0.0f;

        static float get_fps() { return utility::deltaTime > 0.0f ? 1.0f / utility::deltaTime : 0.0f; }
    };
}

#endif //AURA_UTILITY_H

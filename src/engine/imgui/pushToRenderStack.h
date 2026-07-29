//
// Created by ellie on 7/29/26.
//

#pragma once

#include <functional>

namespace Aura {
    class ImGuiRenderExt {
    public:
        static std::vector<std::function<void()>> currentRenderStackQueue;

        static void PushToRenderStack(std::function<void()> function);

        static void ClearRenderStack();
    };
}

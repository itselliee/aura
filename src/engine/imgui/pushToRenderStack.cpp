//
// Created by ellie on 7/29/26.
//

#include <functional>
#include <vector>

#include "pushToRenderStack.h"

namespace Aura {
    std::vector<std::function<void()>> ImGuiRenderExt::currentRenderStackQueue;

    void ImGuiRenderExt::PushToRenderStack(std::function<void()> function) {
        currentRenderStackQueue.push_back(std::move(function));
    }

    void ImGuiRenderExt::ClearRenderStack() {
        currentRenderStackQueue.clear();
    }
}

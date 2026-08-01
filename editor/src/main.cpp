//
// Created by ellie on 7/31/26.
//

#include "app.h"
#include "../ext-layers/panels.h"

int main() {
    auto *app_proc = new aura_core::app();

    app_proc->push_layer(new aura_editor::panels(app_proc, app_proc->get_scene_renderer()));
    app_proc->run();

    return 0;
};

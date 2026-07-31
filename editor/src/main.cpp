//
// Created by ellie on 7/31/26.
//

#include "app.h"
#include "editor-panels/performance_panel.h"

int main() {
    auto *app_proc = new aura_core::app();

    app_proc->push_layer(new aura_editor::performance_panel());
    app_proc->run();

    return 0;
};

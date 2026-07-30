//
// Created by ellie on 7/29/26.
//

#include <application.h>

#include "input.h"
#include "render_pipeline.h"
#include "../include/panel-layer.h"

int main () {
    aura::application* app = new aura::application();
    app->push_layer(new aura::render_pipeline(app->get_window()));
    app->push_layer(new aura::input_layer(app->get_window()));
    app->push_layer(new panel_layer(app->get_window()));

    app->run();

    delete app;
    return 0;
}

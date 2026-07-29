//
// Created by ellie on 7/28/26.
//

#include <iostream>
#include <vector>
#include <string>
#include <memory>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "app/app.h"

int main() {
    auto *app = new Aura::App();

    app->Run();

    return 0;
}

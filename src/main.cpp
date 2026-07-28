//
// Created by ellie on 7/28/26.
//

#include <iostream>
#include <vector>
#include <string>
#include <memory>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "application/Application.h"

int main() {
    auto *app = new Aura::Application();

    app->Run();

    return 0;
}

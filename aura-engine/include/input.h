//
// Created by ellie on 7/30/26.
//

#ifndef AURA_INPUT_H
#define AURA_INPUT_H
#include <iostream>
#include <ostream>

#include "layer.h"

namespace aura {
    class input_layer : public layer {
    public:
        window* m_window;

        input_layer(window* window) : m_window(window) {}

        void on_attach() override {
            std::cout << "input layer running" << std::endl;
            glfwSetWindowUserPointer(m_window->glfw_window(), this);
            glfwSetKeyCallback(m_window->glfw_window(), key_callback);
        }

        static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
            auto* self = static_cast<input_layer*>(glfwGetWindowUserPointer(window));
            if (self) {
                self->on_key_event(window, key, scancode, action, mods);
            }
        }

        void on_update(float deltaTime) override {

        }

    private:
        void on_key_event(GLFWwindow* window, int key, int scancode, int action, int mods) {
            if (action == GLFW_PRESS) {
                const char* name = glfwGetKeyName(key, scancode);

                if (name == nullptr) {
                    switch (key) {
                        case GLFW_KEY_ESCAPE:
                            name = "escape";
                            break;

                        case GLFW_KEY_SPACE:
                            name = "space";
                            break;

                        case GLFW_KEY_LEFT:
                            name = "left";
                            break;

                        case GLFW_KEY_RIGHT:
                            name = "right";
                            break;

                        case GLFW_KEY_UP:
                            name = "up";
                            break;

                        case GLFW_KEY_DOWN:
                            name = "down";
                            break;

                        case GLFW_KEY_PAGE_UP:
                            name = "page-up";
                            break;

                        case GLFW_KEY_PAGE_DOWN:
                            name = "page-down";
                            break;

                        case GLFW_KEY_HOME:
                            name = "home";
                            break;

                        case GLFW_KEY_END:
                            name = "end";
                            break;

                        case GLFW_KEY_BACKSPACE:
                            name = "backspace";
                            break;

                        case GLFW_KEY_DELETE:
                            name = "delete";
                            break;

                        case GLFW_KEY_INSERT:
                            name = "insert";
                            break;

                        case GLFW_KEY_TAB:
                            name = "tab";
                            break;

                        case GLFW_KEY_CAPS_LOCK:
                            name = "capslock";
                            break;

                        case GLFW_KEY_LEFT_SHIFT:
                            name = "left-shift";
                            break;

                        case GLFW_KEY_RIGHT_SHIFT:
                            name = "right-shift";
                            break;

                        case GLFW_KEY_ENTER:
                            name = "enter";
                            break;

                        case GLFW_KEY_LEFT_ALT:
                            name = "left-alt";
                            break;

                        case GLFW_KEY_RIGHT_ALT:
                            name = "right-alt";
                            break;

                        case GLFW_KEY_LEFT_CONTROL:
                            name = "left-control";
                            break;

                        case GLFW_KEY_RIGHT_CONTROL:
                            name = "right-control";
                            break;

                        case GLFW_KEY_LEFT_SUPER:
                            name = "left-super";
                            break;

                        case GLFW_KEY_F1:
                            name = "f1";
                            break;

                        case GLFW_KEY_F2:
                            name = "f2";
                            break;

                        case GLFW_KEY_F3:
                            name = "f3";
                            break;

                        case GLFW_KEY_F4:
                            name = "f4";
                            break;

                        case GLFW_KEY_F5:
                            name = "f5";
                            break;

                        case GLFW_KEY_F6:
                            name = "f6";
                            break;

                        case GLFW_KEY_F7:
                            name = "f7";
                            break;

                        case GLFW_KEY_F8:
                            name = "f8";
                            break;

                        case GLFW_KEY_F9:
                            name = "f9";
                            break;

                        case GLFW_KEY_F10:
                            name = "f10";
                            break;

                        case GLFW_KEY_F11:
                            name = "f11";
                            break;

                        case GLFW_KEY_F12:
                            name = "f12";
                            break;

                        default:
                            name = nullptr;
                            break;
                    }
                }

                std::cout << "input: " << (name ? name : "unknown") << std::endl;
            }
        }
    };
}

#endif //AURA_INPUT_H

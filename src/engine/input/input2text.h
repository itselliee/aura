//
// Created by ellie on 7/29/26.
//

#include "../generalImports.h"

namespace Aura {
    class Input2Text {
    public:
        static std::string getCleanKeyName(int keyId) {

            const char* nativeName = glfwGetKeyName(keyId, 0);
            if (nativeName != nullptr) {
                return std::string(nativeName);
            }

            switch (keyId) {
                case GLFW_KEY_SPACE:         return "SPACE";
                case GLFW_KEY_ESCAPE:        return "ESCAPE";
                case GLFW_KEY_ENTER:         return "ENTER";
                case GLFW_KEY_TAB:           return "TAB";
                case GLFW_KEY_BACKSPACE:     return "BACKSPACE";
                case GLFW_KEY_INSERT:        return "INSERT";
                case GLFW_KEY_DELETE:        return "DELETE";
                case GLFW_KEY_RIGHT:         return "RIGHT ARROW";
                case GLFW_KEY_LEFT:          return "LEFT ARROW";
                case GLFW_KEY_DOWN:          return "DOWN ARROW";
                case GLFW_KEY_UP:            return "UP ARROW";
                case GLFW_KEY_CAPS_LOCK:     return "CAPS LOCK";
                case GLFW_KEY_SCROLL_LOCK:   return "SCROLL LOCK";
                case GLFW_KEY_NUM_LOCK:      return "NUM LOCK";
                case GLFW_KEY_PRINT_SCREEN:  return "PRINT SCREEN";
                case GLFW_KEY_PAUSE:         return "PAUSE";
                case GLFW_KEY_F1:            return "F1";
                case GLFW_KEY_F2:            return "F2";
                case GLFW_KEY_F3:            return "F3";
                case GLFW_KEY_F4:            return "F4";
                case GLFW_KEY_F5:            return "F5";
                case GLFW_KEY_F12:           return "F12";
                case GLFW_KEY_LEFT_SHIFT:    return "LEFT SHIFT";
                case GLFW_KEY_LEFT_CONTROL:  return "LEFT CTRL";
                case GLFW_KEY_LEFT_ALT:      return "LEFT ALT";
                case GLFW_KEY_RIGHT_SHIFT:   return "RIGHT SHIFT";
                case GLFW_KEY_RIGHT_CONTROL: return "RIGHT CTRL";
                case GLFW_KEY_RIGHT_ALT:     return "RIGHT ALT";

                default: return "UNKNOWN_KEY_" + std::to_string(keyId);
            }
        }
    };
}
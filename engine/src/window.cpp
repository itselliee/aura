//
// Created by ellie on 7/31/26.
//

#include "window.h"

#include <iostream>
#include <ostream>

namespace aura_core {
    window::window(int width, int height) {
        std::cout << "window: creating window" << std::endl;

#ifdef IS_LINUX_PLATFORM
        SDL_SetHint(SDL_HINT_VIDEO_DRIVER, "x11");
#endif // keep this in, memory leak kills kids

        if (!SDL_Init(SDL_INIT_VIDEO)) {
            std::cerr << "window: failed to initialize SDL, aborting" << std::endl;
            return;
        }

        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

#ifdef IS_APPLE_PLATFORM
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, SDL_GL_CONTEXT_FORWARD_COMPATIBLE_FLAG);
#endif

        // Created using SDL3 syntax and pixel density flags
        m_window = SDL_CreateWindow("Aura", width, height, SDL_WINDOW_OPENGL | SDL_WINDOW_HIGH_PIXEL_DENSITY);

        if (m_window == nullptr) {
            std::cerr << "window: failed to create SDL window, aborting" << std::endl;
            SDL_Quit();
            return;
        }

        // Create the native context handle
        m_gl_context = SDL_GL_CreateContext(m_window);
        if (m_gl_context == nullptr) {
            std::cerr << "window: failed to create GL context, aborting" << std::endl;
            SDL_DestroyWindow(m_window);
            SDL_Quit();
            return;
        }

        // Initialize GLAD using SDL3's proc address locator
        if (!gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress)) {
            std::cerr << "window: glad init failed, aborting" << std::endl;
            return;
        }

        SDL_GL_SetSwapInterval(0);

        std::cout << "window: initialized successfully" << std::endl;

        return;
    }

    window::~window() {
        std::cout << "window: destroying window" << std::endl;
        if (m_gl_context) {
            SDL_GL_DestroyContext(m_gl_context);
        }
        if (m_window) {
            SDL_DestroyWindow(m_window);
        }
        SDL_Quit();
    }

    void window::refresh() const {
        SDL_GL_SwapWindow(m_window);
    }

    bool window::should_close() const {
        return m_should_close;
    }

    SDL_Window* window::get_window() const {
        return m_window;
    }
}

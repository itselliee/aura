//
// Created by ellie on 7/31/26.
//

#ifndef AURA_WINDOW_H
#define AURA_WINDOW_H

#include <glad/glad.h>
#include <SDL3/SDL.h>
#include <SDL3/SDL_hints.h>

namespace aura_core {
    class window {
    public:
        window(int width, int height);
        virtual ~window();

        void refresh() const;
        bool should_close() const;

        SDL_Window *get_window() const;

        void set_should_close(bool close) { m_should_close = close; }

    private:
        SDL_Window* m_window = nullptr;
        SDL_GLContext m_gl_context = nullptr;

        bool m_should_close = false;
    };
}

#endif //AURA_WINDOW_H

//
// Created by ellie on 7/31/26.
//

#include "app.h"

#include "utility.h"
#include "backends/imgui_impl_sdl3.h"

namespace aura_core {
    app::app() {
        m_window = new window(1280, 720);
        m_layerstack = new layer_stack();
        m_internal_layerstack = new internal_layer_stack();

        m_imgui_renderer = new imgui_renderer(m_window);
        m_scene_renderer = new scene_renderer();

        m_internal_layerstack->push_layer(m_imgui_renderer);
        m_internal_layerstack->push_layer(m_scene_renderer);
    }
    app::~app() {
        delete m_internal_layerstack;
        delete m_layerstack;
        delete m_window;
    }

    void app::run() {
        while (!m_window->should_close() && m_app_running) {
            SDL_Event event;
            while (SDL_PollEvent(&event)) {
                ImGui_ImplSDL3_ProcessEvent(&event);

                switch (event.type) {
                    case SDL_EVENT_QUIT:
                        m_window->set_should_close(true);
                        break;
                    case SDL_EVENT_WINDOW_CLOSE_REQUESTED:
                        if (event.window.windowID == SDL_GetWindowID(m_window->get_window())) {
                            m_window->set_should_close(true);
                        }
                        break;
                    case SDL_EVENT_WINDOW_PIXEL_SIZE_CHANGED:
                        if (event.window.windowID == SDL_GetWindowID(m_window->get_window())) {
                            glViewport(0, 0, event.window.data1, event.window.data2);
                        }
                        break;
                }
            }

            float currentFrame = static_cast<float>((double)SDL_GetTicks() / 1000.0);
            utility::deltaTime = currentFrame - utility::lastFrameTime;
            utility::lastFrameTime = currentFrame;

            for (internal_layer* layer : *m_internal_layerstack) {
                layer->on_update(utility::deltaTime);
            }

            for (layer* layer : *m_layerstack) {
                layer->on_update(utility::deltaTime);
            }

            for (internal_layer* layer : *m_internal_layerstack) {
                layer->pre_render();
            }

            for (layer* layer : *m_layerstack) {
                layer->pre_render();
            }

            for (internal_layer* layer : *m_internal_layerstack) {
                layer->gl_render_stg();
            }

            for (internal_layer* layer : *m_internal_layerstack) {
                layer->imgui_render_stg();
            }

            for (layer* layer : *m_layerstack) {
                layer->on_render();
            }

            for (internal_layer* layer : *m_internal_layerstack) {
                layer->post_render();
            }

            m_window->refresh();
        }

        delete this;
    }

    void app::push_layer(layer* layer) const {
        m_layerstack->push_layer(layer);
    }

    window *app::get_window() const { return m_window; }
    scene_renderer *app::get_scene_renderer() const { return m_scene_renderer; }

}

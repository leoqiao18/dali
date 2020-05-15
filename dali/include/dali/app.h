//
// Created by Leo on 4/23/2020.
//

#ifndef __DALI_APP_H
#define __DALI_APP_H

#include <dali/core.h>
#include <dali/common.h>
#include <dali/window.h>
#include <dali/event.h>
#include <dali/layer.h>
#include <dali/imgui/layer.h>

namespace dali {

    class DALI_API App {
    public:
        App();

        virtual ~App();

        void run();

        void on_event(Event &e);

        bool on_window_close(WindowCloseEvent &e);

        void push_layer(Layer *layer);

        void push_overlay(Layer *layer);

        inline Window &get_window() {
            return *m_window;
        }

        inline static App &get() {
            return *s_instance;
        }

    private:
        std::unique_ptr<Window> m_window;
        ImGuiLayer *m_imgui_layer;
        LayerStack m_layer_stack;
        bool m_running = true;

    private:
        static App *s_instance;
    };

    // This function should be defined in client application
    App *create_app();

}

#endif //__DALI_APP_H

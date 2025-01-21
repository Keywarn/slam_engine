#include "game.h"

#include <slam_window.glfw/window.h>

namespace slam
{
    game::game()
    {
        m_main_window = new window_glfw();
        m_main_window->init(1280, 720, "slam_engine");
        m_renderer = new slam_renderer::renderer(static_cast<window_glfw*>(m_main_window)->get_window());
    }

    game::~game()
    {
    }

    int game::run()
    {
        if (!start())
        {
            return false;
        }

        return loop();
    }

    int game::start()
    {
        return true;
    }

    int game::loop()
    {
        std::chrono::high_resolution_clock::time_point start_time = std::chrono::high_resolution_clock::now();
        auto current_time = start_time;
        float delta = std::chrono::duration<float, std::chrono::seconds::period>(start_time - current_time).count();
        
        while (!is_quitting())
        {
            step(delta);
            auto time_now = std::chrono::high_resolution_clock::now();
            delta = std::chrono::duration<float, std::chrono::seconds::period>(time_now - current_time).count();
            current_time = time_now;
        }

        return true;
    };

    int game::stop()
    {
        return true;
    }

    void game::quit()
    {
        m_quit_requested = true;
    }

    bool game::is_quitting()
    {
        return m_quit_requested;
    }
};
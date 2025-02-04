#include "game.h"

#include <slam_window.glfw/window_glfw.h>
#include <slam_input.glfw/input_manager_glfw.h>

namespace slam
{
    game::game()
    {
        m_main_window = new window_glfw();
        m_main_window->init(1280, 720, "slam_engine");
        m_input_manager = new input_manager_glfw(m_main_window);
        m_renderer = new slam_renderer::renderer(m_main_window);

        start_time = std::chrono::high_resolution_clock::now();
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

    double game::time_since_start()
    {
        std::chrono::high_resolution_clock::time_point current_time = std::chrono::high_resolution_clock::now();
        double time = std::chrono::duration<double, std::chrono::seconds::period>(current_time - start_time).count();

        return time;
    }
};
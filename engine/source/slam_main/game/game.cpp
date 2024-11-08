#include "game.h"

namespace slam
{
    game::game()
    {
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
            current_time = std::chrono::high_resolution_clock::now();
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
#pragma once

#include <slam_utils/patterns/singleton.h>
#include <slam_renderer/renderer.h>
#include <slam_window/window.h>
#include <slam_input/input_manager.h>

#include <chrono>
#include <string>

namespace slam
{
class game : public singleton<game>
{
public:

    game();
    virtual ~game();

    int run();
    void quit();

    double time_since_start();

    input_manager& get_input_manager();

protected:

    virtual int start();
    int loop();
    virtual int stop();

    virtual void step(float delta) {};

    bool is_quitting();

    window* m_main_window = nullptr;
    slam_renderer::renderer* m_renderer = nullptr;
    std::unique_ptr<input_manager> m_input_manager = nullptr;

private:
    inline static game* s_instance = nullptr;
    bool m_quit_requested = false;
    std::chrono::high_resolution_clock::time_point start_time;
};
};
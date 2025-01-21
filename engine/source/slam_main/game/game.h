#pragma once

#include <slam_utils/patterns/singleton.h>
#include <slam_renderer/renderer.h>
#include <slam_window/window.h>

#include <chrono>
#include <string>

namespace slam
{
class game : public singleton<game>
{
public:

    game();
    virtual ~game();

    static game& instance();

    int run();
    void quit();

protected:

    virtual int start();
    int loop();
    virtual int stop();

    virtual void step(float delta) {};

    bool is_quitting();

    window* m_main_window = nullptr;
    slam_renderer::renderer* m_renderer = nullptr;

private:

    inline static game* s_instance = nullptr;
    bool m_quit_requested = false;
};
};
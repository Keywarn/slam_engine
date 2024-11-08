#pragma once

#include <string>
#include <chrono>

#include <slam_utils/patterns/singleton.h>

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

    virtual std::string get_name() = 0;

protected:

    virtual int start();
    int loop();
    virtual int stop();

    virtual void step(float delta) {};

    bool is_quitting();

private:

    inline static game* s_instance = nullptr;
    bool m_quit_requested = false;
};
};
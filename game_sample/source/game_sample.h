#pragma once

#include <slam_main/game/game.h>
#include <slam_renderer/renderer.h>
#include <glfw/glfw3.h>

class game_sample : public slam::game
{
public:
    virtual std::string get_name() override;

protected:
    virtual int start() override;
    virtual int stop() override;

    virtual void step(const float time) override;

private:
    // TODO move this into the engine
    GLFWwindow* m_window;
};
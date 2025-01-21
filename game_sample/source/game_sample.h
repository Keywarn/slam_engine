#pragma once

#include <slam_main/game/game.h>
#include <slam_renderer/renderer.h>

class game_sample : public slam::game
{
public:

protected:
    virtual int start() override;
    virtual int stop() override;

    virtual void step(const float time) override;
};
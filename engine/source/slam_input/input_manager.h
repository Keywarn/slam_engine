#pragma once

#include <array>
#include <string>
#include <glm/glm.hpp>

#include "input_enums.h"

namespace slam
{
enum input_type
{
    glfw,
    none
};

class input_manager
{
public:
    input_manager() = default;
    ~input_manager() = default;

    virtual void init() = 0;
    virtual void update(float delta) = 0;

    virtual bool is_key_down(kbm_key key) = 0;          // Currently down
    virtual bool was_key_pressed(kbm_key key) = 0;      // Pressed this frame
    virtual bool was_key_released(kbm_key key) = 0;     // Released this frame
    virtual bool was_key_hit(kbm_key key) = 0;          // Quickly pressed and released

    virtual std::string get_clipboard_text() = 0;
    virtual void set_clipboard_text(const char* text) = 0;

    virtual glm::vec2 get_mouse_position() = 0;
    virtual void set_mouse_position(const glm::vec2& pos) = 0;

    virtual void set_mouse_hidden(bool hidden) = 0;

protected:
    std::array<unsigned int, (int)kbm_key::count> m_kbm_key_states;
    std::array<double, (int)kbm_key::count> m_key_down_start_time;
};
}
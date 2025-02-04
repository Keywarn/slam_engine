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
    virtual void update(float delta);

    bool is_key_down(kbm_key key);          // Currently down
    bool was_key_pressed(kbm_key key);      // Pressed this frame
    bool was_key_released(kbm_key key);     // Released this frame
    bool was_key_tapped(kbm_key key);       // Quickly pressed and released

    virtual std::string get_clipboard_text() = 0;
    virtual void set_clipboard_text(const char* text) = 0;

    virtual glm::vec2 get_mouse_position() = 0;
    virtual void set_mouse_position(const glm::vec2& pos) = 0;

    virtual void set_mouse_hidden(bool hidden) = 0;

protected:
    void update_key(int key, bool down);
    virtual void get_platform_key_down(size_t key) = 0;

    // Threshold for inputs to count as a 'tap'
    inline static constexpr float k_tap_threshold = 0.3f;

    std::array<unsigned int, (int)kbm_key::count> m_kbm_key_states;
    std::array<double, (int)kbm_key::count> m_kbm_key_down_start_time;
};
}
#include "input_manager.h"

#include <slam_main/game/game.h>

namespace slam
{
void input_manager::update(float delta)
{
    for (size_t key = 0; key < (size_t)kbm_key::mouse_0; key++)
    {
        bool down = (get_platform_key_down(key));
        update_key((int)key, down);
    }

    //TODO mouse handling
}

void input_manager::update_key(int key, bool down)
{
    if (down)
    {
        if ((m_kbm_key_states[key] & (int)key_state_flags::down) != 0)
        {
            // Key was previously down, now set it to only down (and not pressed this frame)
            m_kbm_key_states[key] = (int)key_state_flags::down;
        }
        else
        {
            // Key was pressed this frame
            m_kbm_key_states[key] = (int)key_state_flags::down | (int)key_state_flags::pressed;
            m_kbm_key_down_start_time[key] = game::get_instance()->time_since_start();
        }
    }
    else
    {
        if ((m_kbm_key_states[key] & (int)key_state_flags::down) != 0)
        {
            double hold_time = (game::get_instance()->time_since_start() - m_kbm_key_down_start_time[key]);
            if (hold_time < k_tap_threshold)
            {
                m_kbm_key_states[key] = (int)key_state_flags::tap | (int)key_state_flags::released;
            }
            else
            {
                // Key was previously held rather than tapped so only set released
                m_kbm_key_states[key] = (int)key_state_flags::released;
            }
        }
        else
        {
            m_kbm_key_states[key] = 0;
        }
    }
}

bool input_manager::is_key_down(kbm_key key)
{
    return (m_kbm_key_states[(int)key] & (int)key_state_flags::down) != 0;
}

bool input_manager::was_key_pressed(kbm_key key)
{
    return (m_kbm_key_states[(int)key] & (int)key_state_flags::pressed) != 0;
}

bool input_manager::was_key_released(kbm_key key)
{
    return (m_kbm_key_states[(int)key] & (int)key_state_flags::released) != 0;
}

bool input_manager::was_key_tapped(kbm_key key)
{
    return (m_kbm_key_states[(int)key] & (int)key_state_flags::tap) != 0;
}
}
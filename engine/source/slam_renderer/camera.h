#pragma once

#include <glm/glm.hpp>

#include <slam_window/window.h>

namespace slam_renderer
{

class camera
{
public:
    camera(glm::vec3 position, glm::vec2 window_centre);

    void update(float delta, slam::window* window);

    void first_person_aim(float delta, slam::window* window);
    void move(float delta, slam::window* window);

    void recalculate_projections(slam::window* window);

    glm::vec3 get_position()
    {
        return m_position;
    }

    glm::vec3 get_forwards()
    {
        return m_forwards;
    }

    glm::mat4& get_view()
    {
        return m_view;
    }

    glm::mat4& get_perspective()
    {
        return m_perspective;
    }

    glm::mat4& get_orthographic()
    {
        return m_orthographic;
    }

private:
    glm::vec3 m_position;
    glm::vec3 m_forwards;

    glm::vec3 m_right;
    glm::vec3 m_up;

    float m_yaw = -90.f;
    float m_pitch = 0.f;

    glm::vec2 m_last_cursor_position;

    glm::mat4 m_view;
    glm::mat4 m_perspective;
    glm::mat4 m_orthographic;
    float m_orthographic_size = 1000.f;

    float m_speed = 3.f;
    float m_sensitivity = 0.1f;
};
}


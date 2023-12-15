#pragma once

#include <glm/glm/glm.hpp>
#include <GLFW/glfw3.h>

namespace render_engine
{

class camera
{
public:
    camera(glm::vec3 position, glm::vec2 window_centre);

    void update(float delta, GLFWwindow* window);

    void first_person_aim(float delta, GLFWwindow* window);
    void move(float delta, GLFWwindow* window);

    void recalculate_projections(GLFWwindow* window);

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


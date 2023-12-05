#pragma once

#include <glm/glm/glm.hpp>

namespace render_engine
{

class camera
{
public:
    camera(glm::vec3 position, glm::vec3 target);

    void update(float delta, int window_width, int window_height);


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
    glm::vec3 m_target;
    glm::vec3 m_direction;

    glm::vec3 m_right;
    glm::vec3 m_up;

    glm::mat4 m_view;
    glm::mat4 m_perspective;
    glm::mat4 m_orthographic;
    float m_orthographic_size = 1000.f;
};
}


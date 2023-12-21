#pragma once
#include <glm/glm/glm.hpp>

namespace render_engine
{
class light
{
public:
    light(glm::vec3 position, glm::vec3 colour, float strength);

    const glm::vec3 get_position() const
    {
        return m_position;
    }
    const glm::vec3 get_colour() const
    {
        return m_colour;
    }

private:
    glm::vec3 m_position;
    glm::vec3 m_colour;
    float m_strength;
};

class directional_light : public light
{
public:
    directional_light(glm::vec3 direction, glm::vec3 position, glm::vec3 colour, float strength);

    const glm::vec3& get_direction() const
    {
        return m_direction;
    }

private:
    glm::vec3 m_direction;
};
}


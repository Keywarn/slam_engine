#pragma once
#include <glm/glm/glm.hpp>
#include "shader.h"

namespace render_engine
{
class light
{
public:
    light(glm::vec3 position, glm::vec3 colour, float diffuse, float ambient, float specular);

    void const load_to_shader(std::shared_ptr<shader> shader) const;

private:
    glm::vec3 m_position;
    glm::vec3 m_diffuse;
    glm::vec3 m_ambient;
    glm::vec3 m_specular;
    
};

class directional_light : public light
{
public:
    directional_light(glm::vec3 direction, glm::vec3 position, glm::vec3 colour, float diffuse, float ambient, float specular);

    const glm::vec3& get_direction() const
    {
        return m_direction;
    }

private:
    glm::vec3 m_direction;
};
}


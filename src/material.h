#pragma once
#include <glm/glm/glm.hpp>

#include "texture.h"
#include "shader.h"

namespace render_engine
{
class material
{
public:
    // Just use the texture and set everything else to white
    material(std::shared_ptr<shader> shader, texture* texture, float shininess);
    // Same colour for all and just use strength values
    material(std::shared_ptr<shader> shader, texture* texture, float shininess, glm::vec3 colour, float albedo, float ambient, float specular);
    // Different colours for each property
    material(std::shared_ptr<shader> shader, texture* texture, float shininess, glm::vec3 albedo, glm::vec3 ambient, glm::vec3 specular);

    void use(glm::mat4 transform);

private:
    glm::vec3 m_albedo;
    glm::vec3 m_ambient;
    glm::vec3 m_specular;
    
    float m_shininess;

    texture* m_texture = nullptr;

    std::shared_ptr<shader> m_shader;
};
}


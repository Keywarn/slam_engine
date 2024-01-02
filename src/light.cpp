#include "light.h"

namespace render_engine
{
light::light(glm::vec3 position, glm::vec3 colour, float diffuse, float ambient, float specular)
    : m_position(position)
    , m_diffuse(colour * diffuse)
    , m_ambient(colour * ambient)
    , m_specular(colour * specular)
{

}

void const light::load_to_shader(std::shared_ptr<shader> shader) const
{
    shader->set_vec3("u_light.diffuse", m_diffuse);
    shader->set_vec3("u_light.ambient", m_ambient);
    shader->set_vec3("u_light.specular", m_specular);
    shader->set_vec3("u_light.position", m_position);
}

directional_light::directional_light(glm::vec3 direction, glm::vec3 position, glm::vec3 colour, float diffuse, float ambient, float specular)
    : light(position, colour, diffuse, ambient, specular)
    , m_direction(direction)
{

}
}
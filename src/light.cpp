#include "light.h"

namespace render_engine
{
light::light(glm::vec3 position, glm::vec3 colour, float diffuse, float ambient, float specular)
    : m_position(position)
    , m_diffuse(colour * diffuse)
    , m_ambient(colour * ambient)
    , m_specular(colour * specular)
{
    m_type = light_type::none;
}

void light::load_to_shader(std::shared_ptr<shader> shader) const
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
    m_type = light_type::directional;
}

void directional_light::load_to_shader(std::shared_ptr<shader> shader) const
{
    light::load_to_shader(shader);

    shader->set_vec3("u_light.direction", m_direction);
}

point_light::point_light(float constant, float linear, float quadratic, glm::vec3 position, glm::vec3 colour, float diffuse, float ambient, float specular)
    : light(position, colour, diffuse, ambient, specular)
    , m_constant(constant)
    , m_linear(linear)
    , m_quadratic(quadratic)
{
    m_type = light_type::point;
}

void point_light::load_to_shader(std::shared_ptr<shader> shader) const
{
    light::load_to_shader(shader);

    shader->set_float("u_light.constant", m_constant);
    shader->set_float("u_light.linear", m_linear);
    shader->set_float("u_light.quadratic", m_quadratic);
}

spot_light::spot_light(float angle, float outer_angle, glm::vec3 direction, glm::vec3 position, glm::vec3 colour, float diffuse, float ambient, float specular)
    : light(position, colour, diffuse, ambient, specular)
    , m_angle(angle)
    , m_outer_angle(outer_angle)
    , m_direction(direction)
{
    m_type = light_type::spot;
}

void spot_light::load_to_shader(std::shared_ptr<shader> shader) const
{
    light::load_to_shader(shader);

    shader->set_float("u_light.angle_cos", glm::cos(glm::radians(m_angle)));
    shader->set_float("u_light.outer_angle_cos", glm::cos(glm::radians(m_outer_angle)));
    shader->set_vec3("u_light.direction", m_direction);
}
}
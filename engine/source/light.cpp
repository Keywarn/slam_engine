#include "light.h"

#include "renderer.h"

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

void light::load_to_shader(std::shared_ptr<shader> shader, std::string prefix) const
{
    shader->set_vec3(prefix + ".light.diffuse", m_diffuse);
    shader->set_vec3(prefix + ".light.ambient", m_ambient);
    shader->set_vec3(prefix + ".light.specular", m_specular);
    // Position is handled by derived light as not all types need it (directional)
}

directional_light::directional_light(glm::vec3 direction, glm::vec3 position, glm::vec3 colour, float diffuse, float ambient, float specular)
    : light(position, colour, diffuse, ambient, specular)
    , m_direction(direction)
{
    m_type = light_type::directional;
    m_shadow_map = renderer::get_instance()->register_framebuffer(render_engine::framebuffer_type::depth, nullptr, 1024, 1024);
}

void directional_light::load_to_shader(std::shared_ptr<shader> shader, std::string prefix) const
{
    light::load_to_shader(shader, prefix);

    shader->set_vec3(prefix + ".direction", m_direction);
    // TODO hardcoded slot value
    glActiveTexture(GL_TEXTURE2);
    m_shadow_map->get_texture()->bind();
}

point_light::point_light(float constant, float linear, float quadratic, glm::vec3 position, glm::vec3 colour, float diffuse, float ambient, float specular)
    : light(position, colour, diffuse, ambient, specular)
    , m_constant(constant)
    , m_linear(linear)
    , m_quadratic(quadratic)
{
    m_type = light_type::point;
}

void point_light::load_to_shader(std::shared_ptr<shader> shader, std::string prefix) const
{
    light::load_to_shader(shader, prefix);
    shader->set_vec3(prefix + ".light.position", m_position);

    shader->set_float(prefix + ".constant", m_constant);
    shader->set_float(prefix + ".linear", m_linear);
    shader->set_float(prefix + ".quadratic", m_quadratic);
}

spot_light::spot_light(float angle, float outer_angle, glm::vec3 direction, glm::vec3 position, glm::vec3 colour, float diffuse, float ambient, float specular)
    : light(position, colour, diffuse, ambient, specular)
    , m_angle(angle)
    , m_outer_angle(outer_angle)
    , m_direction(direction)
{
    m_type = light_type::spot;
}

void spot_light::load_to_shader(std::shared_ptr<shader> shader, std::string prefix) const
{
    light::load_to_shader(shader, prefix);
    shader->set_vec3(prefix + ".light.position", m_position);

    shader->set_float(prefix + ".angle_cos", glm::cos(glm::radians(m_angle)));
    shader->set_float(prefix + ".outer_angle_cos", glm::cos(glm::radians(m_outer_angle)));
    shader->set_vec3(prefix + ".direction", m_direction);
}
}
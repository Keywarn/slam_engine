#include "material.h"

#include "renderer.h"

namespace render_engine
{
// TODO make these call the most descriptive ctor so we can do any processing for all
// Just use the texture and set everything else to white
material::material(std::shared_ptr<shader> shader, texture* texture, float shininess)
    : m_shader(shader)
    , m_texture(texture)
    , m_albedo(glm::vec3(1.f))
    , m_ambient(glm::vec3(1.f))
    , m_specular(glm::vec3(1.f))
    , m_shininess(shininess)
{

}

// Same colour for all and just use strength values
material::material(std::shared_ptr<shader> shader, texture* texture, float shininess, glm::vec3 colour, float albedo, float ambient, float specular)
    : m_shader(shader)
    , m_texture(texture)
    , m_albedo(colour * albedo)
    , m_ambient(colour* ambient)
    , m_specular(colour* specular)
    , m_shininess(shininess)
{

}

// Different colours for each property
material::material(std::shared_ptr<shader> shader, texture* texture, float shininess, glm::vec3 albedo, glm::vec3 ambient, glm::vec3 specular)
    : m_shader(shader)
    , m_texture(texture)
    , m_albedo(albedo)
    , m_ambient(ambient)
    , m_specular(specular)
    , m_shininess(shininess)
{

}

void material::use(glm::mat4 transform)
{

    // TODO don't know if we need to do this every frame, also need to come up with a mode for when we don't have a texture and just want a colour
    if (m_texture != nullptr)
    {
        glBindTexture(GL_TEXTURE_2D, m_texture->get_id());
    }

    m_shader->use();

    renderer* renderer = renderer::get_instance();

    m_shader->set_mat4("transform", transform);
    m_shader->set_mat4("view", renderer->get_view());
    m_shader->set_mat4("projection", renderer->get_projection());

    m_shader->set_vec3("u_material.albedo", m_albedo);
    if (m_shader->get_type() != shader_type::unlit)
    {
        m_shader->set_vec3("u_material.ambient", m_ambient);
        m_shader->set_vec3("u_material.specular", m_specular);
        m_shader->set_float("u_material.shininess", m_shininess);
    }
}
}
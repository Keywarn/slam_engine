#include "material.h"

#include "renderer.h"

namespace render_engine
{
// TODO make these call the most descriptive ctor so we can do any processing for all
// Just use the texture and set everything else to white
material::material(std::shared_ptr<shader> shader, std::shared_ptr<texture> texture, float shininess)
    : m_shader(shader)
    , m_albedo_texture(texture)
    , m_albedo(glm::vec3(1.f))
    , m_specular(glm::vec3(1.f))
    , m_shininess(shininess)
{

}

// Same colour for all and just use strength values
material::material(std::shared_ptr<shader> shader, std::shared_ptr<texture> texture, float shininess, glm::vec3 colour, float albedo, float specular)
    : m_shader(shader)
    , m_albedo_texture(texture)
    , m_albedo(colour * albedo)
    , m_specular(colour* specular)
    , m_shininess(shininess)
{

}

// Different colours for each property
material::material(std::shared_ptr<shader> shader, std::shared_ptr<texture> texture, float shininess, glm::vec3 albedo, glm::vec3 specular)
    : m_shader(shader)
    , m_albedo_texture(texture)
    , m_albedo(albedo)
    , m_specular(specular)
    , m_shininess(shininess)
{
    m_shader->use();
    if (m_albedo_texture != nullptr)
    {
        int albedo = glGetUniformLocation(m_shader->m_id, "u_material.albedo_texture");

        if (albedo == -1)
        {
            std::cout << "ERROR::MATERIAL::COULD NOT SET ALBEDO TEXTURE EVEN THOUGH TEXTURE IS DEFINED: " << std::endl;
            return;
        }
        glUniform1i(albedo, 0);

    }
}

void material::use(glm::mat4 transform)
{
    m_shader->use();

    // TODO don't know if we need to do this every frame - only if there is a different texture loaded?
    if (m_albedo_texture != nullptr)
    {
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, m_albedo_texture->get_id());
        m_shader->set_bool("u_material.sample_albedo", true);
    }

    if (m_specular_map != nullptr)
    {
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, m_specular_map->get_id());
        m_shader->set_bool("u_material.sample_specular", true);
    }    

    renderer* renderer = renderer::get_instance();

    m_shader->set_mat4("transform", transform);
    m_shader->set_mat4("view", renderer->get_view());
    m_shader->set_mat4("projection", renderer->get_projection());

    m_shader->set_vec3("u_material.albedo", m_albedo);
    if (m_shader->get_type() != shader_type::unlit)
    {
        m_shader->set_vec3("u_material.specular", m_specular);
        m_shader->set_float("u_material.shininess", m_shininess);

        //TODO this should probably be handled by some kind of 'light' object
        const directional_light* sun = renderer::get_instance()->get_sun();
        sun->load_to_shader(m_shader);
        m_shader->set_vec3("camera_position", renderer::get_instance()->get_camera()->get_position());
    }
}
}
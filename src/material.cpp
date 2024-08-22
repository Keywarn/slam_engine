#include "material.h"

#include "renderer.h"

#include <format>

#define MAX_NUM_POINT_LIGHTS 4

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

        m_albedo_texture->bind();
        if (m_shader->get_type() == shader_type::lit)
        {
            m_shader->set_bool("u_material.sample_albedo", true);
        }
    }
    else if(m_shader->get_type() != shader_type::shadow_pass)
    {
        m_shader->set_bool("u_material.sample_albedo", false);
    }

    if (m_specular_map != nullptr)
    {
        glActiveTexture(GL_TEXTURE1);
        m_specular_map->bind();
        m_shader->set_bool("u_material.sample_specular", true);
    }
    else if(m_shader->get_type() != shader_type::shadow_pass)
    {
        m_shader->set_bool("u_material.sample_specular", false);
    }

    renderer* renderer = renderer::get_instance();

    if (m_shader->get_type() != shader_type::unlit_cube && m_shader->get_type() != shader_type::shadow_pass)
    {
        m_shader->set_vec3("u_camera_position", renderer::get_instance()->get_camera()->get_position());
        m_shader->set_vec3("u_material.albedo", m_albedo);
        m_shader->set_mat4("transform", transform);
        m_shader->set_mat4("view", renderer->get_view());

        m_shader->set_vec3("u_material.albedo", m_albedo);
    }
    else if(m_shader->get_type() != shader_type::shadow_pass)
    {
        glm::mat4 view = glm::mat4(glm::mat3(renderer->get_view()));
        m_shader->set_mat4("view", view);
        
    }
    if (m_shader->get_type() != shader_type::shadow_pass)
    {
        m_shader->set_mat4("projection", renderer->get_projection());
    }

    if (m_shader->get_type() == shader_type::shadow_pass)
    {
        glm::mat4 light_space_matrix;
        light_space_matrix = renderer->get_current_pass_directional_light()->get_light_space_matrix();
        m_shader->set_mat4("transform", transform);
        m_shader->set_mat4("light_space_matrix", light_space_matrix);
    }

    if (m_shader->get_type() == shader_type::lit)
    {
        m_shader->set_vec3("u_material.specular", m_specular);
        m_shader->set_float("u_material.shininess", m_shininess);
        glm::mat4 light_space_matrix;
        light_space_matrix = renderer->get_current_pass_directional_light()->get_light_space_matrix();
        m_shader->set_mat4("light_space_matrix", light_space_matrix);

        size_t point_count = 0;
        for (auto& light : renderer->get_lights())
        {
            switch (light->get_type())
            {
            case (light_type::directional):
            {
                light->load_to_shader(m_shader, "u_directional_light");
                break;
            }
            case (light_type::point):
            {
                light->load_to_shader(m_shader, std::format("u_point_lights[{}]", point_count));
                point_count = (point_count + 1) % MAX_NUM_POINT_LIGHTS;
                break;
            }
            case (light_type::spot):
            {
                light->load_to_shader(m_shader, "u_spot_light");
                break;
            }
            default:
            {
                std::cout << "ERROR::MATERIAL::LIGHT TYPE NOT SUPPORTED: " << (int)light->get_type() << std::endl;
            }
            }
            
       }
    }
    
}

void material::post_draw()
{
    m_shader->post_draw();
}
}
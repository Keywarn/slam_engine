#pragma once
#include <glm/glm.hpp>

#include "texture.h"
#include "shader.h"

namespace slam_renderer
{

class material
{
public:
    // Just use the texture and set everything else to white
    material(std::shared_ptr<shader> shader, std::shared_ptr<texture> texture, float shininess)
        : material(shader, texture, shininess, glm::vec3(1.f), glm::vec3(1.f)) {};
    // Same colour for all and just use strength values
    material(std::shared_ptr<shader> shader, std::shared_ptr<texture> texture, float shininess, glm::vec3 colour, float albedo, float specular)
        : material(shader, texture, shininess, colour* albedo, colour* specular) {};
    // Different colours for each property
    material(std::shared_ptr<shader> shader, std::shared_ptr<texture> texture, float shininess, glm::vec3 albedo, glm::vec3 specular);

    void set_specular_map(std::shared_ptr<texture> texture)
    {
        m_specular_map = texture;

        m_shader->use();
        int specular = glGetUniformLocation(m_shader->m_id, "u_material.specular_map");

        if (specular == -1)
        {
            std::cout << "ERROR::MATERIAL::COULD NOT SET SPECULAR MAP EVEN THOUGH TEXTURE IS DEFINED " << std::endl;
            return;
        }
        glUniform1i(specular, 1);
    }

    void use(glm::mat4 transform);

    void post_draw();

    void set_name(std::string name)
    {
        m_name = name;
    }

    const shader_type get_shader_type() const
    {
        return m_shader->get_type();
    }

    const std::string& get_name() const
    {
        return m_name;
    }

private:
    std::string m_name;
    glm::vec3 m_albedo;
    glm::vec3 m_specular;
    
    float m_shininess;

    std::shared_ptr<texture> m_albedo_texture = nullptr;
    std::shared_ptr<texture> m_specular_map = nullptr;

    std::shared_ptr<shader> m_shader;
};
}


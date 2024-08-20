#pragma once
#include <glm/glm/glm.hpp>
#include <glm/glm/gtc/matrix_transform.hpp>
#include "shader.h"
#include "framebuffer.h"

namespace render_engine
{

    enum class light_type {
        none,
        directional,
        point,
        spot
    };

class light
{
public:
    light(glm::vec3 position, glm::vec3 colour, float diffuse, float ambient, float specular);

    virtual void load_to_shader(std::shared_ptr<shader> shader, std::string prefix) const;

    light_type get_type() const
    {
        return m_type;
    }

    std::shared_ptr<framebuffer> get_shadow_map()
    {
        return m_shadow_map;
    }

    const glm::vec3& get_position() const
    {
        return m_position;
    }

protected:
    glm::vec3 m_position;
    glm::vec3 m_diffuse;
    glm::vec3 m_ambient;
    glm::vec3 m_specular;

    light_type m_type;
    std::shared_ptr<framebuffer> m_shadow_map = nullptr; // Currently only supported on direcitonal lights
};

class directional_light : public light
{
public:
    directional_light(glm::vec3 direction, glm::vec3 position, glm::vec3 colour, float diffuse, float ambient, float specular);

    void load_to_shader(std::shared_ptr<shader> shader, std::string prefix) const override;
    const glm::vec3& get_direction() const
    {
        return m_direction;
    }

    const glm::mat4 get_light_space_matrix()
    {
        glm::mat4 view = glm::lookAt(m_position, m_position + m_direction, glm::vec3(0.f, 1.f, 0.f));
        
        float near_plane = 0.5f, far_plane = 100.f;
        glm::mat4 projection = glm::ortho(-10.0f, 10.0f, -10.0f, 10.0f, near_plane, far_plane);

        return projection * view;
    }

private:
    glm::vec3 m_direction;
};

class point_light : public light
{
public:
    point_light(float constant, float linear, float quadratic, glm::vec3 position, glm::vec3 colour, float diffuse, float ambient, float specular);

    void load_to_shader(std::shared_ptr<shader> shader, std::string prefix) const override;

private:
    float m_constant;
    float m_linear;
    float m_quadratic;
};

class spot_light : public light
{
public:
    spot_light(float angle, float outer_angle, glm::vec3 direction, glm::vec3 position, glm::vec3 colour, float diffuse, float ambient, float specular);

    void load_to_shader(std::shared_ptr<shader> shader, std::string prefix) const override;

private:
    float m_angle;
    float m_outer_angle;
    glm::vec3 m_direction;
};
}


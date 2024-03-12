#pragma once
#include <glm/glm/glm.hpp>
#include "shader.h"

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

    virtual void load_to_shader(std::shared_ptr<shader> shader) const;

protected:
    glm::vec3 m_position;
    glm::vec3 m_diffuse;
    glm::vec3 m_ambient;
    glm::vec3 m_specular;

    light_type m_type;
};

class directional_light : public light
{
public:
    directional_light(glm::vec3 direction, glm::vec3 position, glm::vec3 colour, float diffuse, float ambient, float specular);

    void load_to_shader(std::shared_ptr<shader> shader) const override;
    const glm::vec3& get_direction() const
    {
        return m_direction;
    }

private:
    glm::vec3 m_direction;
};

class point_light : public light
{
public:
    point_light(float constant, float linear, float quadratic, glm::vec3 position, glm::vec3 colour, float diffuse, float ambient, float specular);

    void load_to_shader(std::shared_ptr<shader> shader) const override;

private:
    float m_constant;
    float m_linear;
    float m_quadratic;
};

class spot_light : public light
{
public:
    spot_light(float angle, float outer_angle, glm::vec3 direction, glm::vec3 position, glm::vec3 colour, float diffuse, float ambient, float specular);

    void load_to_shader(std::shared_ptr<shader> shader) const override;

private:
    float m_angle;
    float m_outer_angle;
    glm::vec3 m_direction;
};
}


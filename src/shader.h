#pragma once

#include <glad/glad.h> // include glad to get all the required OpenGL headers
#include <glm/glm/glm.hpp>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

#include "texture.h"

namespace render_engine
{
enum class shader_type
{
    lit,
    unlit
};

class shader
{
public:
    shader(const char* vertex_path, const char* frament_path, glm::vec3 albedo, texture* texture, shader_type type = shader_type::unlit);

    void use();

    void set_bool(const std::string& name, bool value) const;
    void set_int(const std::string& name, int value) const;
    void set_float(const std::string& name, float value) const;
    void set_vec3(const std::string& name, glm::vec3& vec) const;
    void set_mat4(const std::string& name, glm::mat4& mat) const;

    void free();

public:

    unsigned int m_id;

private:
    glm::vec3 m_albedo = glm::vec3(0.f);
    texture* m_texture = nullptr;

    shader_type m_type = shader_type::unlit;
};
}
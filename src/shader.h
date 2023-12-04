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
class shader
{
public:
    shader(const char* vertex_path, const char* frament_path, texture* texture);

    void use();

    void set_bool(const std::string& name, bool value) const;
    void set_int(const std::string& name, int value) const;
    void set_float(const std::string& name, float value) const;
    void set_mat4(const std::string& name, glm::mat4& mat) const;

    void free();

public:

    unsigned int m_id;

private:
    texture* m_texture;
};
}
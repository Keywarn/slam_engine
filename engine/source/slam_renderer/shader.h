#pragma once

#include <glm/glm.hpp>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

#include "texture.h"

#define SHADER_VERBOSE_ERRORS 1

namespace slam_renderer
{
enum class shader_type
{
    lit,
    unlit,
    unlit_cube, // Doesn't write to depth
    shadow_pass
};

class shader
{
public:
    shader(const char* vertex_path, const char* frament_path, shader_type type = shader_type::unlit);

    void use();
    void post_draw();

    void set_bool(const std::string& name, bool value) const;
    void set_int(const std::string& name, int value) const;
    void set_float(const std::string& name, float value) const;
    void set_vec3(const std::string& name, const glm::vec3& vec) const;
    void set_mat4(const std::string& name, const glm::mat4& mat) const;

    void free();

    const shader_type get_type() const
    {
        return m_type;
    }

public:

    unsigned int m_id;

private:
    shader_type m_type = shader_type::unlit;
    // Used for debug info
    std::string m_vertex_path;
    std::string m_fragment_path;
};
}
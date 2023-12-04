#pragma once

#include <glad/glad.h> // include glad to get all the required OpenGL headers

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

namespace renderer
{
class shader
{
public:
    shader(const char* vertex_path, const char* frament_path);

    void use();

    void set_bool(const std::string &name, bool value) const;
    void set_int(const std::string &name, int value) const;
    void set_float(const std::string &name, float value) const;

    void free();

public:

    unsigned int m_id;
};
}
#include "shader.h"

namespace renderer
{
shader::shader(const char* vertex_path, const char* fragment_path)
{
    // Read in the vertex shader
    std::ifstream vertex_shader_file(vertex_path, std::fstream::in);
    vertex_shader_file.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    std::string vertex_shader_source;
    if (vertex_shader_file.is_open())
    {
        try
        {
            vertex_shader_source = std::string(std::istreambuf_iterator<char>(vertex_shader_file), std::istreambuf_iterator<char>());
        }
        catch(std::ifstream::failure e)
        {
            std::cout << "ERROR::SHADER::VERTEX::COULD NOT READ\n" << std::endl;
        }
    }
    else
    {
        std::cout << "ERROR::SHADER::VERTEX::COULD NOT OPEN\n" << std::endl;
    }

    const char* vertex_shader_source_c = vertex_shader_source.c_str();

    // Read in fragment shader
    std::ifstream fragment_shader_file(fragment_path, std::fstream::in);
    fragment_shader_file.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    std::string fragment_shader_source;
    if (fragment_shader_file.is_open())
    {
        try
        {
            fragment_shader_source = std::string(std::istreambuf_iterator<char>(fragment_shader_file), std::istreambuf_iterator<char>());
        }
        catch (std::ifstream::failure e)
        {
            std::cout << "ERROR::SHADER::FRAGMENT::COULD NOT READ\n" << std::endl;
        }
    }
    else
    {
        std::cout << "ERROR::SHADER::FRAGMENT::COULD NOT OPEN\n" << std::endl;
    }

    const char* fragment_shader_source_c = fragment_shader_source.c_str();
    
    // Compile vertex shader
    int success;

    unsigned int vertex_shader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex_shader, 1, &vertex_shader_source_c, nullptr);
    glCompileShader(vertex_shader);
    glGetShaderiv(vertex_shader, GL_COMPILE_STATUS, &success);

    if (!success)
    {
        char infoLog[512];
        glGetShaderInfoLog(vertex_shader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    // Compile fragment shader
    unsigned int fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment_shader, 1, &fragment_shader_source_c, nullptr);
    glCompileShader(fragment_shader);
    glGetShaderiv(fragment_shader, GL_COMPILE_STATUS, &success);

    if (!success)
    {
        char infoLog[512];
        glGetShaderInfoLog(fragment_shader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    // Compile the shader program
    m_id = glCreateProgram();
    glAttachShader(m_id, vertex_shader);
    glAttachShader(m_id, fragment_shader);
    glLinkProgram(m_id);

    glGetProgramiv(m_id, GL_LINK_STATUS, &success);
    if (!success)
    {
        char infoLog[512];
        glGetProgramInfoLog(m_id, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }

    // Delete the shaders
    glDeleteShader(vertex_shader);
    glDeleteShader(fragment_shader);
}

void shader::use()
{
    glUseProgram(m_id);
}

void shader::set_bool(const std::string& name, bool value) const
{
    glUniform1i(glGetUniformLocation(m_id, name.c_str()), (int)value);
}
void shader::set_int(const std::string& name, int value) const
{
    glUniform1i(glGetUniformLocation(m_id, name.c_str()), value);
}
void shader::set_float(const std::string& name, float value) const
{
    glUniform1f(glGetUniformLocation(m_id, name.c_str()), value);
}

void shader::free()
{
    glDeleteProgram(m_id);
}
}
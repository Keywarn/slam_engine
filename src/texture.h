#pragma once

#include <string>
#include <glad/glad.h>


namespace render_engine
{
enum class texture_type
{
    texture_2d,
    cubemap,
};

class texture
{
public:
    texture(std::string path, texture_type type = texture_type::texture_2d);

    texture(unsigned int width, unsigned int height);

    void free();

    const unsigned int get_id() const
    {
        return m_id;
    }

    const std::string& get_path() const
    {
        return m_path;
    }

    const texture_type get_type() const
    {
        return m_type;
    }

    void bind() const
    {
        glBindTexture(get_gl_type(), m_id);
    }

private:
    void load_face(std::string path, GLenum target, bool generate_mips);

    const GLenum get_gl_type() const
    {
        switch(m_type)
        {
        case texture_type::texture_2d:
        {
            return GL_TEXTURE_2D;
        }
        case texture_type::cubemap:
        {
            return GL_TEXTURE_CUBE_MAP;
        }
        }
    }

private:

    texture_type m_type;
    int m_width;
    int m_height;
    int m_channels;

    unsigned int m_id = 0;

    std::string m_path;
};
}


#pragma once

#include <string>
#include <glad/glad.h>


namespace render_engine
{
enum class texture_type
{
    texture_2d,
    depth_2d,
    cubemap,
};

class texture
{
public:
    texture(std::string path, texture_type type = texture_type::texture_2d, bool isSRGB = false);

    texture(unsigned int width, unsigned int height, texture_type type = texture_type::texture_2d, bool isSRGB = false);

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
        glBindTexture(get_gl_target(), m_id);
    }

private:
    void load_face(std::string path, GLenum target, bool generate_mips);

    const GLenum get_gl_target() const
    {
        switch(m_type)
        {
        case texture_type::texture_2d:
        case texture_type::depth_2d:
        {
            return GL_TEXTURE_2D;
        }
        case texture_type::cubemap:
        {
            return GL_TEXTURE_CUBE_MAP;
        }
        }
    }

    void get_gl_formats(GLenum& internal_format, GLenum& format, GLenum& pixel_type)
    {
        internal_format = GL_RED;
        format = GL_RED;
        pixel_type = GL_UNSIGNED_BYTE;
        if (m_channels == 1 && m_type == texture_type::depth_2d)
        {
            internal_format = GL_DEPTH_COMPONENT;
            format = GL_DEPTH_COMPONENT;
            pixel_type = GL_FLOAT;
        }
        if (m_channels == 3)
        {
            internal_format = m_isSRGB ? GL_SRGB : GL_RGB;
            format = GL_RGB;
        }
        else if (m_channels == 4)
        {
            internal_format = m_isSRGB ? GL_SRGB_ALPHA : GL_RGBA;
            format = GL_RGBA;
        }
    }

private:

    texture_type m_type;
    int m_width;
    int m_height;
    int m_channels;
    bool m_isSRGB = false;

    unsigned int m_id = 0;

    std::string m_path;
};
}


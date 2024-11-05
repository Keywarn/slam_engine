#include "texture.h"

#include <stb_image.h>
#include <iostream>

namespace slam_renderer
{
texture::texture(std::string path, texture_type type, bool isSRGB, int samples)
    : m_path(path)
    , m_type(type)
    , m_samples(samples)
    , m_isSRGB(isSRGB)
{
    GLenum target = get_gl_target();

    glGenTextures(1, &m_id);
    glBindTexture(target, m_id);

    stbi_set_flip_vertically_on_load(m_type != texture_type::cubemap);

    if (m_type == texture_type::texture_2d)
    {
        load_face(path, target, true);
    }
    else if (m_type == texture_type::cubemap)
    {
        for (unsigned int i = 0; i < 6; ++i)
        {
            std::string name = path.substr(0, path.find_last_of('.'));
            std::string extension = path.substr(path.find_last_of('.'));
            load_face(name + "_" + std::to_string(i) + extension, GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, false);
        }
    }
    else
    {
        std::cout << "ERROR::TEXTURE::UNSUPPORTED TEXTURE TYPE:  " << (int)m_type << std::endl;
    }
    set_gl_params(target);
    glBindTexture(target, 0);
}

texture::texture(unsigned int width, unsigned int height, texture_type type, bool isSRGB, int samples)
    : m_path("")
    , m_type(type)
    , m_width(width)
    , m_height(height)
    , m_channels(type == texture_type::depth_2d ? 1 : 4)
    , m_samples(samples)
    , m_isSRGB(isSRGB)
{
    glGenTextures(1, &m_id);

    GLenum target = get_gl_target();
    GLenum internal_format, format, pixel_type;
    get_gl_formats(internal_format, format, pixel_type);

    glBindTexture(target, m_id);
    if (samples > 1)
    {
        glTexImage2DMultisample(target, m_samples, internal_format, width, height, GL_TRUE);
    }
    else
    {
        glTexImage2D(target, 0, internal_format, width, height, 0, format, pixel_type, NULL);
    }

    set_gl_params(target);
    glBindTexture(target, 0);
}

void texture::load_face(std::string path, GLenum target, bool generate_mips)
{
    unsigned char* data = stbi_load(path.c_str(), &m_width, &m_height, &m_channels, 0);

    if (!data)
    {
        std::cout << "ERROR::TEXTURE::FAILED TO READ DATA: " << path << std::endl;
        stbi_image_free(data);
        return;
    }
    
    GLenum internal_format, format, pixel_type;
    get_gl_formats(internal_format, format, pixel_type);

    glTexImage2D(target, 0, internal_format, m_width, m_height, 0, format, pixel_type, data);
    
    if (generate_mips)
    {
        glGenerateMipmap(target);
    }

    stbi_image_free(data);
}

void texture::set_gl_params(GLenum target)
{
    switch (m_type)
    {
    case texture_type::texture_2d:
    {
        glTexParameteri(target, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(target, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        break;
    }
    case texture_type::depth_2d:
    {
        glTexParameteri(target, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(target, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(target, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
        glTexParameteri(target, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
        float border_colour[] = { 1.0f, 1.0f, 1.0f, 1.0f };
        glTexParameterfv(target, GL_TEXTURE_BORDER_COLOR, border_colour);
        break;
    }
    case texture_type::cubemap:
    {
        glTexParameteri(target, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(target, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(target, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(target, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(target, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
        break;
    }
    default:
    {
        std::cout << "ERROR::TEXTURE::NO GL PARAMS FOR TYPE " << std::endl;
        break;
    }
    }
}

void texture::free()
{

}

}
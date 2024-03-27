#include "texture.h"

#include <stb_image/stb_image.h>
#include <iostream>

namespace render_engine
{
texture::texture(std::string path, texture_type type)
    : m_path(path)
    , m_type(type)
{
    GLenum target = GL_TEXTURE_2D;

    if (m_type == texture_type::cubemap)
    {
        target = GL_TEXTURE_CUBE_MAP;
    }
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
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
    }
    else
    {
        std::cout << "ERROR::TEXTURE::UNSUPPORTED TEXTURE TYPE:  " << (int)m_type << std::endl;
    }
}

texture::texture(unsigned int width, unsigned int height)
    : m_path("")
    , m_type(texture_type::texture_2d)
    , m_width(width)
    , m_height(height)
    , m_channels(4)
{
    glGenTextures(1, &m_id);
    glBindTexture(GL_TEXTURE_2D, m_id);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
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
    
    GLenum format = GL_RED;
    if (m_channels == 3)
        format = GL_RGB;
    else if (m_channels == 4)
        format = GL_RGBA;

    glTexImage2D(target, 0, format, m_width, m_height, 0, format, GL_UNSIGNED_BYTE, data);
    
    if (generate_mips)
    {
        glGenerateMipmap(target);
    }

    stbi_image_free(data);
}

void texture::free()
{

}

}
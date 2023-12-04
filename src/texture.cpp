#include "texture.h"

#include <stb_image/stb_image.h>
#include <iostream>

namespace renderer
{
texture::texture(const char* path)
{
    unsigned char* data = stbi_load(path, &m_width, &m_height, &m_channels, 0);

    if (!data)
    {
        std::cout << "ERROR::TEXTURE::FAILED TO READ DATA: " << path << std::endl;
        stbi_image_free(data);
        return;
    }

    glGenTextures(1, &m_id);
    glBindTexture(GL_TEXTURE_2D, m_id);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, m_width, m_height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);

    stbi_image_free(data);
}

void texture::free()
{

}

}
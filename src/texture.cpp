#include "texture.h"

#include <stb_image/stb_image.h>
#include <iostream>

namespace render_engine
{
texture::texture(const char* path)
{
    stbi_set_flip_vertically_on_load(true);
    unsigned char* data = stbi_load(path, &m_width, &m_height, &m_channels, 0);

    if (!data)
    {
        std::cout << "ERROR::TEXTURE::FAILED TO READ DATA: " << path << std::endl;
        stbi_image_free(data);
        return;
    }

    glGenTextures(1, &m_id);

    GLenum format = GL_RED;
    if (m_channels == 3)
        format = GL_RGB;
    else if (m_channels == 4)
        format = GL_RGBA;

    glBindTexture(GL_TEXTURE_2D, m_id);
    glTexImage2D(GL_TEXTURE_2D, 0, format, m_width, m_height, 0, format, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);

    stbi_image_free(data);
}

void texture::free()
{

}

}
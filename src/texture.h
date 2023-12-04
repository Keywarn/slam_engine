#pragma once

#include <glad/glad.h>

namespace renderer
{

class texture
{
public:
    texture(const char* path);

    void free();

    const unsigned int get_id() const
    {
        return m_id;
    }
private:

    int m_width;
    int m_height;
    int m_channels;

    unsigned int m_id = 0;
};
}


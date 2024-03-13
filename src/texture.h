#pragma once

#include <string>
#include <glad/glad.h>


namespace render_engine
{

class texture
{
public:
    texture(std::string path);

    void free();

    const unsigned int get_id() const
    {
        return m_id;
    }

    const std::string& get_path() const
    {
        return m_path;
    }
private:

    int m_width;
    int m_height;
    int m_channels;

    unsigned int m_id = 0;

    std::string m_path;
};
}


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

private:
    void load_face(std::string path, GLenum target, bool generate_mips);
private:

    texture_type m_type;
    int m_width;
    int m_height;
    int m_channels;

    unsigned int m_id = 0;

    std::string m_path;
};
}


#pragma once

namespace slam
{
enum window_type
{
    glfw,
    none
};

class window
{
public:
    window() = default;
    ~window() = default;

    virtual bool init(unsigned int width, unsigned int height, const char* title) = 0;
    virtual void resize(unsigned int width, unsigned int height) = 0;
    virtual void set_title(const char* name) = 0;

    unsigned int get_width()
    {
        return m_width;
    }

    unsigned int get_height()
    {
        return m_height;
    }

protected:
    unsigned int m_width = 0;
    unsigned int m_height = 0;

    const char* m_title = "";
    window_type m_type = none;

};
}
#pragma once

namespace slam
{
enum class window_type
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
    virtual void update(float data) = 0;
    virtual void resize(unsigned int width, unsigned int height) = 0;
    virtual void set_title(const char* name) = 0;

    virtual void get_cursor_position(double* x, double* y) = 0;

    unsigned int get_width()
    {
        return m_width;
    }

    unsigned int get_height()
    {
        return m_height;
    }

    void get_dimensions(unsigned int* width, unsigned int* height)
    {
        *width = m_width;
        *height = m_height;
    }

    bool get_dirty()
    {
        return m_dirty;
    }

    void set_dirty(bool dirty)
    {
        m_dirty = dirty;
    }

protected:
    unsigned int m_width = 0;
    unsigned int m_height = 0;

    const char* m_title = "";
    window_type m_type = window_type::none;
    bool m_dirty = false;

};
}
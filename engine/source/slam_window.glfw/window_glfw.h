#pragma once

#include <slam_window/window.h>

#include <glad.h>
#include <glfw/glfw3.h>

namespace slam
{
    class window_glfw : public window
    {
    public:
        window_glfw() {};

        bool init(unsigned int width, unsigned int height, const char* title) override;
        void update(float delta) override;
        void resize(unsigned int width, unsigned int height) override;
        void set_title(const char* name) override;

        void get_cursor_position(double* x, double* y) override;

        GLFWwindow* get_window()
        {
            return m_window;
        }

    private:
        GLFWwindow* m_window = nullptr;
    };
}
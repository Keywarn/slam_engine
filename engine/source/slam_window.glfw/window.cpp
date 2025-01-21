#include "window.h"

#include <iostream>

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    slam::window_glfw* window_glfw = static_cast<slam::window_glfw*>(glfwGetWindowUserPointer(window));
    window_glfw->resize(width, height);
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, true);
    }

    // TODO actual input handling 
    /*if (key == GLFW_KEY_L && action == GLFW_PRESS)
    {
        slam_renderer::renderer::get_instance()->toggle_wireframe();
    }

    if (key == GLFW_KEY_O && action == GLFW_PRESS)
    {
        slam_renderer::renderer::get_instance()->toggle_persepctive();
    }

    if (key == GLFW_KEY_C && action == GLFW_PRESS)
    {
        cursor_enabled = !cursor_enabled;
        int mode = cursor_enabled ? GLFW_CURSOR_NORMAL : GLFW_CURSOR_DISABLED;
        glfwSetInputMode(window, GLFW_CURSOR, mode);
    }*/
}

namespace slam
{
bool window_glfw::init(unsigned int width, unsigned int height, const char* title)
{
    m_width = width;
    m_height = height;
    m_title = title;
    m_type = glfw;

    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_SAMPLES, 4);

    m_window = glfwCreateWindow(m_width, m_height, m_title, nullptr, nullptr);
    if (m_window == nullptr)
    {
        std::cout << "Failed to create GLFW Window" << std::endl;
        glfwTerminate();
        return false;
    }
    glfwMakeContextCurrent(m_window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return false;
    }

    glfwSetWindowUserPointer(m_window, this);
    glfwSetFramebufferSizeCallback(m_window, framebuffer_size_callback);
    glfwSetKeyCallback(m_window, key_callback);
    glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    return true;
}

void window_glfw::resize(unsigned int width, unsigned int height)
{
    glViewport(0, 0, width, height);
    // TODO Make the renderer recalc matrices if dirty
    m_dirty_size = true;
}

void window_glfw::set_title(const char* name)
{
    // TODO GLFW SPECIFICS
}
}
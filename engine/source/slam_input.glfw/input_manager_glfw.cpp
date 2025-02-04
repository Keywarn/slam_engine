#include "input_manager_glfw.h"

#include <iostream>

namespace slam
{
input_manager_glfw::input_manager_glfw(window* window)
    : m_window(dynamic_cast<window_glfw*>(window))
{
    m_input_type = input_type::glfw;
}

bool input_manager_glfw::get_platform_key_down(size_t key)
{
    return glfwGetKey(m_window->get_window(), g_kbm_key_to_scanecode[key]) == GLFW_PRESS;
}

std::string input_manager_glfw::get_clipboard_text()
{
    __debugbreak();
    //TODO
    return "";
}

void input_manager_glfw::set_clipboard_text(const char* text)
{
    __debugbreak();
    //TODO
}

glm::vec2 input_manager_glfw::get_mouse_position()
{
    __debugbreak();
    //TODO
    return glm::vec2();
}

void input_manager_glfw::set_mouse_position(const glm::vec2& pos)
{
    __debugbreak();
    //TODO
}

void input_manager_glfw::set_mouse_hidden(bool hidden)
{
    __debugbreak();
    //TODO
}
}
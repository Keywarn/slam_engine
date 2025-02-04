#pragma once

#include <slam_input/input_manager.h>
#include <slam_window.glfw/window_glfw.h>

#include <glfw/glfw3.h>

namespace slam
{
    class input_manager_glfw : public input_manager
    {
    public:
        input_manager_glfw(window* window);

        std::string get_clipboard_text() override;
        void set_clipboard_text(const char* text) override;

        glm::vec2 get_mouse_position() override;
        void set_mouse_position(const glm::vec2& pos) override;

        void set_mouse_hidden(bool hidden) override;

    private:
        bool get_platform_key_down(size_t key) override;

        window_glfw* m_window;

    };
}

namespace
{
int g_kbm_key_to_scanecode[(int)slam::kbm_key::count] = {

        0,

        GLFW_KEY_A,
        GLFW_KEY_B,
        GLFW_KEY_C,
        GLFW_KEY_D,
        GLFW_KEY_E,
        GLFW_KEY_F,
        GLFW_KEY_G,
        GLFW_KEY_H,
        GLFW_KEY_I,
        GLFW_KEY_J,
        GLFW_KEY_K,
        GLFW_KEY_L,
        GLFW_KEY_M,
        GLFW_KEY_N,
        GLFW_KEY_O,
        GLFW_KEY_P,
        GLFW_KEY_Q,
        GLFW_KEY_R,
        GLFW_KEY_S,
        GLFW_KEY_T,
        GLFW_KEY_U,
        GLFW_KEY_V,
        GLFW_KEY_W,
        GLFW_KEY_X,
        GLFW_KEY_Y,
        GLFW_KEY_Z,

        GLFW_KEY_1,
        GLFW_KEY_2,
        GLFW_KEY_3,
        GLFW_KEY_4,
        GLFW_KEY_5,
        GLFW_KEY_6,
        GLFW_KEY_7,
        GLFW_KEY_8,
        GLFW_KEY_9,
        GLFW_KEY_0,

        GLFW_KEY_ENTER,
        GLFW_KEY_ESCAPE,
        GLFW_KEY_BACKSPACE,
        GLFW_KEY_TAB,
        GLFW_KEY_SPACE,
        GLFW_KEY_MINUS,
        GLFW_KEY_EQUAL,
        GLFW_KEY_LEFT_BRACKET,
        GLFW_KEY_RIGHT_BRACKET,
        GLFW_KEY_BACKSLASH,

        GLFW_KEY_SEMICOLON,
        GLFW_KEY_APOSTROPHE,
        GLFW_KEY_GRAVE_ACCENT,
        GLFW_KEY_COMMA,
        GLFW_KEY_PERIOD,
        GLFW_KEY_SLASH,

        GLFW_KEY_CAPS_LOCK,

        GLFW_KEY_F1,
        GLFW_KEY_F2,
        GLFW_KEY_F3,
        GLFW_KEY_F4,
        GLFW_KEY_F5,
        GLFW_KEY_F6,
        GLFW_KEY_F7,
        GLFW_KEY_F8,
        GLFW_KEY_F9,
        GLFW_KEY_F10,
        GLFW_KEY_F11,
        GLFW_KEY_F12,
        GLFW_KEY_F13,
        GLFW_KEY_F14,
        GLFW_KEY_F15,
        GLFW_KEY_F16,
        GLFW_KEY_F17,
        GLFW_KEY_F18,
        GLFW_KEY_F19,
        GLFW_KEY_F20,
        GLFW_KEY_F21,
        GLFW_KEY_F22,
        GLFW_KEY_F23,
        GLFW_KEY_F24,

        GLFW_KEY_PRINT_SCREEN,
        GLFW_KEY_SCROLL_LOCK,
        GLFW_KEY_PAUSE,
        GLFW_KEY_INSERT,
        GLFW_KEY_HOME,
        GLFW_KEY_PAGE_UP,
        GLFW_KEY_DELETE,
        GLFW_KEY_END,
        GLFW_KEY_PAGE_DOWN,

        GLFW_KEY_RIGHT,
        GLFW_KEY_LEFT,
        GLFW_KEY_DOWN,
        GLFW_KEY_UP,

        GLFW_KEY_KP_DIVIDE,
        GLFW_KEY_KP_MULTIPLY,
        GLFW_KEY_KP_SUBTRACT,
        GLFW_KEY_KP_ADD,
        GLFW_KEY_KP_ENTER,
        GLFW_KEY_KP_1,
        GLFW_KEY_KP_2,
        GLFW_KEY_KP_3,
        GLFW_KEY_KP_4,
        GLFW_KEY_KP_5,
        GLFW_KEY_KP_6,
        GLFW_KEY_KP_7,
        GLFW_KEY_KP_8,
        GLFW_KEY_KP_9,
        GLFW_KEY_KP_0,
        GLFW_KEY_KP_DECIMAL,

        GLFW_KEY_LEFT_CONTROL,
        GLFW_KEY_LEFT_SHIFT,
        GLFW_KEY_LEFT_ALT,
        GLFW_KEY_LEFT_SUPER,
        GLFW_KEY_RIGHT_CONTROL,
        GLFW_KEY_RIGHT_SHIFT,
        GLFW_KEY_RIGHT_ALT,
        GLFW_KEY_RIGHT_SUPER,

        // mouse 0-5
        0,
        0,
        0,
        0,
        0,
        0,

        // modifiers
        0,
        0,
        0,
        0

};
}
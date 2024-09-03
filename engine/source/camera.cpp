#include "camera.h"

#include <glm/gtc/matrix_transform.hpp>
#include <algorithm>

namespace render_engine
{
static const glm::vec3 world_up = glm::vec3(0.0f, 1.0f, 0.0f);

camera::camera(glm::vec3 position, glm::vec2 window_centre)
    : m_position(position)
    , m_last_cursor_position(window_centre)
{
    m_up = world_up;
    m_right = glm::vec3(1.0f, 0.f, 0.f);
    m_forwards = glm::vec3(0.0f, 0.f, -1.f);

    m_view = glm::lookAt(m_position, m_position + m_forwards, m_up);
}

void camera::update(float delta, GLFWwindow* window)
{
    first_person_aim(delta, window);
    move(delta, window);

    m_view = glm::lookAt(m_position, m_position + m_forwards, m_up);
}

void camera::first_person_aim(float delta, GLFWwindow* window)
{
    double cursor_x, cursor_y;
    glfwGetCursorPos(window, &cursor_x, &cursor_y);

    glm::vec2 cursor_delta = { cursor_x - m_last_cursor_position.x, m_last_cursor_position.y - cursor_y };
    m_last_cursor_position = { cursor_x, cursor_y };

    cursor_delta *= m_sensitivity;

    m_yaw += cursor_delta.x;
    m_pitch += cursor_delta.y;

    m_pitch = std::min(m_pitch, 89.0f);
    m_pitch = std::max(m_pitch, -89.0f);

    glm::vec3 direction;
    direction.x = cos(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));
    direction.y = sin(glm::radians(m_pitch));
    direction.z = sin(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));
    m_forwards = direction;

    m_right = glm::normalize(glm::cross(m_forwards, world_up));
    m_up = glm::normalize(glm::cross(m_right, m_forwards));
}

void camera::move(float delta, GLFWwindow* window)
{
    glm::vec3 camera_move(0.f);

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
    {
        camera_move.z += 1.f;
    }
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
    {
        camera_move.z -= 1.f;
    }
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
    {
        camera_move.x -= 1.f;
    }
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
    {
        camera_move.x += 1.f;
    }
    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
    {
        camera_move.y += 1.f;
    }
    if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
    {
        camera_move.y -= 1.f;
    }

    camera_move *= m_speed * delta;

    m_position += m_right * camera_move.x + world_up * camera_move.y + m_forwards * camera_move.z;
}

void camera::recalculate_projections(GLFWwindow* window)
{
    int window_width, window_height;
    glfwGetWindowSize(window, &window_width, &window_height);

    // Recalculate projections
    m_perspective = glm::perspective(glm::radians(45.0f), (float)window_width / (float)window_height, 0.1f, 100.0f);
    m_orthographic = glm::ortho(-window_width / m_orthographic_size, window_width / m_orthographic_size, -window_height / m_orthographic_size, window_height / m_orthographic_size, 0.01f, 100.0f);
}
}   
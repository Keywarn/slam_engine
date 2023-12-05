#include "camera.h"

#include <glm/glm/gtc/matrix_transform.hpp>

namespace render_engine
{
camera::camera(glm::vec3 position)
    : m_position(position)
{
    m_up = glm::vec3(0.0f, 1.0f, 0.0f);
    m_right = glm::vec3(1.0f, 0.f, 0.f);
    m_forwards = glm::vec3(0.0f, 0.f, -1.f);

    m_view = glm::lookAt(m_position, m_position + m_forwards, m_up);
}

void camera::update(float delta, GLFWwindow* window)
{
    move(delta, window);

    m_view = glm::lookAt(m_position, m_position + m_forwards, m_up);
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

    camera_move *= m_speed * delta;

    m_position += m_right * camera_move.x + m_up * camera_move.y + m_forwards * camera_move.z;
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
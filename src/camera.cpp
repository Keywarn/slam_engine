#include "camera.h"

#include <glm/glm/gtc/matrix_transform.hpp>

namespace render_engine
{
camera::camera(glm::vec3 position, glm::vec3 target)
    : m_position(position)
    , m_target(target)
{
    m_direction = glm::normalize(m_position - m_target);

    glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
    glm::vec3 m_right = glm::normalize(glm::cross(up, m_direction));

    m_view = glm::lookAt(position, target, up);
}

void camera::update(float delta, int window_width, int window_height)
{
    // Recalculate projections
    m_perspective = glm::perspective(glm::radians(45.0f), (float)window_width / (float)window_height, 0.1f, 100.0f);
    m_orthographic = glm::ortho(-window_width / m_orthographic_size, window_width / m_orthographic_size, -window_height / m_orthographic_size, window_height / m_orthographic_size, 0.01f, 100.0f);
}
}   
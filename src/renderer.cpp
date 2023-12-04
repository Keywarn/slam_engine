#include "renderer.h"

namespace render_engine
{

renderer::renderer(GLFWwindow* window)
    : m_window(window)
{
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    m_orthographic = glm::ortho(0.0f, 800.0f, 0.0f, 600.0f, 0.1f, 100.0f);
    recalculate_projection();

    // Camera setup
    m_view = glm::mat4(1.0f);
    m_view = glm::translate(m_view, glm::vec3(0.0f, 0.0f, -3.0f));
}

void renderer::toggle_wireframe()
{
    m_wireframe = !m_wireframe;

    GLenum mode = m_wireframe ? GL_LINE : GL_FILL;

    glPolygonMode(GL_FRONT_AND_BACK, mode);
}

void renderer::toggle_persepctive()
{
    m_perspective = !m_perspective;
}

void renderer::render()
{
    glClear(GL_COLOR_BUFFER_BIT);

    for (mesh& mesh : m_meshes)
    {
        mesh.draw();
    }
}
texture* renderer::register_texture(const char* path)
{
    m_textures.push_back(texture(path));
    return &m_textures.back();
}

shader* renderer::register_shader(const char* vertex_path, const char* fragment_path, texture* texture)
{
    m_shaders.push_back(shader(vertex_path, fragment_path, texture));
    return &m_shaders.back();
}

mesh* renderer::register_mesh(vertices vertices, faces faces, shader* shader, glm::mat4 transform)
{
    m_meshes.push_back(mesh(this, vertices, faces, shader, transform));
    return &m_meshes.back();
}

void renderer::recalculate_projection()
{
    int width, height;
    glfwGetWindowSize(m_window, &width, &height);
    m_projection = glm::perspective(glm::radians(45.0f), (float)width / (float)height, 0.1f, 100.0f);
}

void renderer::free()
{
    for (mesh& mesh : m_meshes)
    {
        mesh.free();
    }

    for (shader& shader : m_shaders)
    {
        shader.free();
    }

    for (texture& texture : m_textures)
    {
        texture.free();
    }
}

}


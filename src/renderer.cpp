#include "renderer.h"

namespace renderer
{

renderer::renderer(GLFWwindow* window)
    : m_window(window)
{
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
}

void renderer::toggle_wireframe()
{
    m_wireframe = !m_wireframe;

    GLenum mode = m_wireframe ? GL_LINE : GL_FILL;

    glPolygonMode(GL_FRONT_AND_BACK, mode);
}

void renderer::render()
{
    glClear(GL_COLOR_BUFFER_BIT);

    for (mesh& mesh : m_meshes)
    {
        mesh.draw();
    }
}
shader* renderer::register_shader(const char* vertex_path, const char* fragment_path)
{
    m_shaders.push_back(shader(vertex_path, fragment_path));
    return &m_shaders.back();
}

mesh* renderer::register_mesh(vertices vertices, faces faces, shader* shader)
{
    m_meshes.push_back(mesh(vertices, faces, shader));
    return &m_meshes.back();
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
}

}


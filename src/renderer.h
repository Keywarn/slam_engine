#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm/glm.hpp>
#include <glm/glm/gtc/matrix_transform.hpp>

#include <iostream>
#include <fstream>
#include <vector>

#include "shader.h"
#include "mesh.h"
#include "texture.h"

namespace render_engine
{
class renderer
{
public:
    renderer(GLFWwindow* window);

    void render();

    void toggle_wireframe();
    void toggle_persepctive();

    texture* register_texture(const char* path);
    shader* register_shader(const char* vertex_path, const char* fragment_path, texture* texture);
    mesh* register_mesh(vertices vertices, faces faces, shader* shader, glm::mat4 transform);

    void recalculate_projection();

    void free();

    glm::mat4& get_view()
    {
        return m_view;
    }

    glm::mat4& get_projection()
    {
        return m_perspective ? m_projection : m_orthographic;
    }

private:
    GLFWwindow* m_window;

    std::vector<texture> m_textures;
    std::vector<shader> m_shaders;
    std::vector<mesh> m_meshes;

    glm::mat4 m_projection;
    glm::mat4 m_orthographic;

    glm::mat4 m_view;

    bool m_wireframe = false;
    bool m_perspective = true;
};
}
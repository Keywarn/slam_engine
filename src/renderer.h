#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <fstream>
#include <vector>

#include "shader.h"
#include "mesh.h"

namespace renderer
{
class renderer
{
public:
    renderer(GLFWwindow* window);

    void render();

    void toggle_wireframe();

    shader* register_shader(const char* vertex_path, const char* fragment_path);
    mesh* register_mesh(vertices vertices, faces faces, shader* shader);

    void free();

private:
    GLFWwindow* m_window;

    std::vector<shader> m_shaders;
    std::vector<mesh> m_meshes;

    bool m_wireframe = false;
};
}
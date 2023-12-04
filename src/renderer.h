#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <fstream>
#include <vector>

#include "shader.h"
#include "mesh.h"
#include "texture.h"

namespace renderer
{
class renderer
{
public:
    renderer(GLFWwindow* window);

    void render();

    void toggle_wireframe();

    texture* register_texture(const char* path);
    shader* register_shader(const char* vertex_path, const char* fragment_path, texture* texture);
    mesh* register_mesh(vertices vertices, faces faces, shader* shader, glm::mat4 transform);

    void free();

private:
    GLFWwindow* m_window;

    std::vector<texture> m_textures;
    std::vector<shader> m_shaders;
    std::vector<mesh> m_meshes;


    bool m_wireframe = false;
};
}
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
#include "camera.h"
#include "singleton.h"
#include "light.h"
#include "material.h"

namespace render_engine
{

class renderer : public singleton<renderer>
{
public:
    friend class singleton;
    renderer(GLFWwindow* window);

    void render(float delta);

    void toggle_wireframe();
    void toggle_persepctive();

    std::shared_ptr<texture> register_texture(const char* path);
    std::shared_ptr<shader> register_shader(const char* vertex_path, const char* fragment_path, shader_type type = shader_type::unlit);
    void register_material(std::shared_ptr<material> material);
    mesh* register_mesh(vertices vertices, faces faces, std::shared_ptr<render_engine::material> material, glm::mat4 transform);

    std::shared_ptr<directional_light> register_directional_light(glm::vec3 direction, glm::vec3 position, glm::vec3 colour, float diffuse, float ambient, float specular);
    std::shared_ptr<point_light> register_point_light(float constant, float linear, float quadratic, glm::vec3 position, glm::vec3 colour, float diffuse, float ambient, float specular);
    std::shared_ptr<spot_light> register_spot_light(float angle, float outer_angle, glm::vec3 direction, glm::vec3 position, glm::vec3 colour, float diffuse, float ambient, float specular);

    void free();

    glm::mat4& get_view()
    {
        return m_camera->get_view();
    }

    glm::mat4& get_projection()
    {
        return m_perspective ? m_camera->get_perspective() : m_camera->get_orthographic();
    }

    camera* get_camera()
    {
        return m_camera;
    }

    const std::vector<std::shared_ptr<light>>& get_lights() const
    {
        return m_lights;
    }

private:
    GLFWwindow* m_window;
    camera* m_camera;

    std::vector<std::shared_ptr<texture>> m_textures;
    std::vector<std::shared_ptr<shader>> m_shaders;
    std::vector<std::shared_ptr<material>> m_materials;
    std::vector<mesh> m_meshes;

    std::vector<std::shared_ptr<light>> m_lights;

    bool m_wireframe = false;
    bool m_perspective = true;
};
}
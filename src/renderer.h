#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm/glm.hpp>
#include <glm/glm/gtc/matrix_transform.hpp>

#include <iostream>
#include <fstream>
#include <vector>

#include "shader.h"
#include "model.h"
#include "texture.h"
#include "camera.h"
#include "singleton.h"
#include "light.h"
#include "material.h"
#include "framebuffer.h"

namespace render_engine
{

class renderer : public singleton<renderer>
{
public:
    friend class singleton;
    renderer(GLFWwindow* window);

    void render(float delta);
    void draw_models(float delta, std::shared_ptr<material> override_material = nullptr);
    void post_render(float delta);

    void toggle_wireframe();
    void toggle_persepctive();

    std::shared_ptr<texture> get_register_texture(std::string path, bool isSRGB = false, texture_type type = texture_type::texture_2d, int width = 0, int height = 0);
    std::shared_ptr<shader> register_shader(const char* vertex_path, const char* fragment_path, shader_type type = shader_type::unlit);
    void register_material(std::shared_ptr<material> material);
    model* register_model(std::string path, glm::mat4 transform, unsigned int shader_index = 0);

    std::shared_ptr<directional_light> register_directional_light(glm::vec3 direction, glm::vec3 position, glm::vec3 colour, float diffuse, float ambient, float specular);
    std::shared_ptr<point_light> register_point_light(float constant, float linear, float quadratic, glm::vec3 position, glm::vec3 colour, float diffuse, float ambient, float specular);
    std::shared_ptr<spot_light> register_spot_light(float angle, float outer_angle, glm::vec3 direction, glm::vec3 position, glm::vec3 colour, float diffuse, float ambient, float specular);

    std::shared_ptr<framebuffer> register_framebuffer(framebuffer_type type, std::shared_ptr<render_engine::shader> shader, int width = 0, int height = 0);

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

    const std::shared_ptr<material> find_material(std::string name)
    {
        if (name.empty())
        {
            std::cout << "ERROR::MATERIAL::CANNOT FETCH A MATERIAL WITH BLANK NAME" << std::endl;
            return nullptr;
        }
        auto predicate = [name](std::shared_ptr<material>& material)
            {
                return material->get_name() == name;
            };

        if (const auto it = std::find_if(m_materials.begin(), m_materials.end(), predicate); it != m_materials.end())
        {
            return *it;
        }
        else
        {
            return nullptr;
        }

    }

    const std::shared_ptr<shader> get_shader(unsigned int index)
    {
        if (index >= m_shaders.size())
        {
            std::cout << "ERROR::SHADER::OUT OF BOUNDS index: " << index << std::endl;
            return nullptr;
        }

        return m_shaders[index];
    }

    void get_resolution(int* width, int* height) const
    {
        glfwGetWindowSize(m_window, width, height);
    }

    std::shared_ptr<directional_light> get_current_pass_directional_light()
    {
        return m_current_pass_directional_light;
    }

private:
    GLFWwindow* m_window;
    camera* m_camera;

    std::vector<std::shared_ptr<texture>> m_textures;
    std::vector<std::shared_ptr<shader>> m_shaders;
    std::vector<std::shared_ptr<material>> m_materials;
    std::vector<model> m_models;

    std::vector<std::shared_ptr<framebuffer>> m_framebuffers;

    std::vector<std::shared_ptr<light>> m_lights;
    std::shared_ptr<directional_light> m_current_pass_directional_light;

    bool m_wireframe = false;
    bool m_perspective = true;
};
}
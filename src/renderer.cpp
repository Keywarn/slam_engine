#include "renderer.h"

namespace render_engine
{

renderer::renderer(GLFWwindow* window)
    : m_window(window)
{
    int window_width, window_height;
    glfwGetWindowSize(window, &window_width, &window_height);
    m_camera = new camera(glm::vec3(0.f, 0.f, 5.f), { window_width / 2.f, window_height / 2.f });
    
    m_camera->recalculate_projections(m_window);
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glEnable(GL_DEPTH_TEST);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
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

void renderer::render(float delta)
{
    m_camera->update(delta, m_window);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    for (mesh& mesh : m_meshes)
    {
        mesh.draw(delta);
    }
}
std::shared_ptr<texture> renderer::register_texture(const char* path)
{
    std::shared_ptr<texture> texture_ptr = std::make_shared<texture>(path);
    m_textures.push_back(texture_ptr);
    return texture_ptr;
}

std::shared_ptr<shader> renderer::register_shader(const char* vertex_path, const char* fragment_path, shader_type type)
{
    std::shared_ptr<shader> shader_ptr = std::make_shared<shader>(shader(vertex_path, fragment_path, type));
    m_shaders.push_back(shader_ptr);
    return shader_ptr;
}

void renderer::register_material(std::shared_ptr<material> material)
{
    m_materials.push_back(material);
}

mesh* renderer::register_mesh(vertices vertices, faces faces, std::shared_ptr<render_engine::material> material, glm::mat4 transform)
{
    m_meshes.push_back(mesh(vertices, faces, material, transform));
    return &m_meshes.back();
}

std::shared_ptr<directional_light> renderer::register_directional_light(glm::vec3 direction, glm::vec3 position, glm::vec3 colour, float diffuse, float ambient, float specular)
{
    std::shared_ptr<directional_light> light_ptr = std::make_shared<directional_light>(direction, position, colour, diffuse, ambient, specular);
    m_lights.push_back(light_ptr);
    return light_ptr;
}

std::shared_ptr<point_light> renderer::register_point_light(float constant, float linear, float quadratic, glm::vec3 position, glm::vec3 colour, float diffuse, float ambient, float specular)
{
    std::shared_ptr<point_light> light_ptr = std::make_shared<point_light>(constant, linear, quadratic, position, colour, diffuse, ambient, specular);
    m_lights.push_back(light_ptr);
    return light_ptr;
}

std::shared_ptr<spot_light> renderer::register_spot_light(float angle, float outer_angle, glm::vec3 direction, glm::vec3 position, glm::vec3 colour, float diffuse, float ambient, float specular)
{
    std::shared_ptr<spot_light> light_ptr = std::make_shared<spot_light>(angle, outer_angle, direction, position, colour, diffuse, ambient, specular);
    m_lights.push_back(light_ptr);
    return light_ptr;
}

void renderer::free()
{
    for (mesh& mesh : m_meshes)
    {
        mesh.free();
    }

    for (auto& shader : m_shaders)
    {
        shader->free();
    }

    for (auto& texture : m_textures)
    {
        texture->free();
    }
}

}


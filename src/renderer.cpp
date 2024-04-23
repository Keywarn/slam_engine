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
        glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
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

        if (m_framebuffers.size() > 0)
        {
            m_framebuffers.at(0)->bind();
        }

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        for (model& model : m_models)
        {
            model.draw(delta);
        }

        if (m_framebuffers.size() > 0)
        {
            bool was_wireframe = m_wireframe;
            if (m_wireframe)
            {
                toggle_wireframe();
            }
            glBindFramebuffer(GL_FRAMEBUFFER, 0);
            m_framebuffers.at(0)->draw(delta);

            if (was_wireframe)
            {
                toggle_wireframe();
            }
        }
    }
    std::shared_ptr<texture> renderer::get_register_texture(std::string path, texture_type type, int width, int height)
    {
        auto predicate = [path](std::shared_ptr<texture>& texture)
            {
                return !path.empty() && texture->get_path() == path;
            };

        if (!path.empty())
        {
            if (const auto it = std::find_if(m_textures.begin(), m_textures.end(), predicate); it != m_textures.end())
            {
                return *it;
            }
        }

        // Texture not found or path was empty so cannot be used to compare
        std::shared_ptr<texture> texture_ptr = nullptr;
        if (!path.empty())
        {
            std::cout << "TEXTURE::REGISTER: " << path << std::endl;
            texture_ptr = std::make_shared<texture>(path, type);
        }
        else if (width > 0 && height > 0)
        {
            std::cout << "TEXTURE::REGISTER: " << width << "x" << height << std::endl;
            texture_ptr = std::make_shared<texture>(width, height);
        }
        else
        {
            std::cout << "ERROR::TEXTURE::REGISTER: Invalid texture params: " << path << " | " << width << "x" << height << std::endl;
        }

        if (texture_ptr != nullptr)
        {
            m_textures.push_back(texture_ptr);
        }
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
        std::cout << "MATERIAL::REGISTER: " << material->get_name() << std::endl;
        m_materials.push_back(material);
    }

    model* renderer::register_model(std::string path, glm::mat4 transform, unsigned int shader_index)
    {
        m_models.push_back(model(path, transform, shader_index));
        return &m_models.back();
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

    std::shared_ptr<framebuffer> renderer::register_framebuffer(framebuffer_type type, std::shared_ptr<shader> shader)
    {
        int width, height;
        get_resolution(&width, &height);
        std::shared_ptr<framebuffer> framebuffer_ptr = std::make_shared<framebuffer>(width, height, shader, type);
        m_framebuffers.push_back(framebuffer_ptr);
        return framebuffer_ptr;
    }

void renderer::free()
{
    for (auto& framebuffer : m_framebuffers)
    {
        framebuffer->free();
    }

    for (model& model : m_models)
    {
        model.free();
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


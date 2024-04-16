#pragma once

#include <iostream>

#include <glad/glad.h>

#include "texture.h"
#include "shader.h"

namespace render_engine
{

enum class framebuffer_type
{
    colour,
    depth_stencil
};

class framebuffer
{
public:
    framebuffer(unsigned int width, unsigned int height, std::shared_ptr<shader> shader, framebuffer_type type = framebuffer_type::colour);

    void setup_quad();
    
    void draw(float delta);

    void bind();

    void free()
    {
        if (m_render_buffer_object != 0)
        {
            glDeleteRenderbuffers(GL_RENDERBUFFER, &m_render_buffer_object);
        }

        glDeleteFramebuffers(1, &m_id);
    }

    const std::shared_ptr<texture> get_texture() const
    {
        return m_texture;
    }

private:
    unsigned int m_width = 0;
    unsigned int m_height = 0;
    unsigned int m_id = 0;

    //vbo
    // TODO create some kind of abstract VBO class so that we can do this in the same place as meshes
    unsigned int m_vertex_array, m_vertex_buffer = 0;

    std::shared_ptr<shader> m_shader = nullptr;

    framebuffer_type m_type = framebuffer_type::colour;

    std::shared_ptr<texture> m_texture = nullptr;
    unsigned int m_render_buffer_object = 0;
};
}
#pragma once

#include <glad.h>

#include <iostream>

#include "texture.h"
#include "shader.h"

namespace slam_renderer
{

enum class framebuffer_type
{
    // Colour
    colour,
    colour_depth_stencil,
    // No Colour
    no_colour,
    depth
};

class framebuffer
{
public:
    framebuffer(unsigned int width, unsigned int height, unsigned int samples, std::shared_ptr<shader> shader, framebuffer_type type = framebuffer_type::colour);

    void setup_quad();
    
    void draw(float delta, bool draw_multisampled = false);

    void bind(bool draw_multisampled = false);

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

    const int get_width() const
    {
        return m_width;
    }

    const int get_height() const
    {
        return m_height;
    }

private:
    unsigned int m_width = 0;
    unsigned int m_height = 0;
    unsigned int m_samples = 0;
    unsigned int m_id = 0;

    //vbo
    // TODO create some kind of abstract VBO class so that we can do this in the same place as meshes
    unsigned int m_vertex_array, m_vertex_buffer = 0;

    std::shared_ptr<shader> m_shader = nullptr;

    framebuffer_type m_type = framebuffer_type::colour;

    std::shared_ptr<texture> m_texture = nullptr;
    unsigned int m_render_buffer_object = 0;

    // Intermediates for sampling
    unsigned int m_sample_id = 0;
    std::shared_ptr<texture> m_sample_texture = nullptr;
    unsigned int m_samlpe_render_buffer_object = 0;
};
}
#pragma once

#include <iostream>

#include <glad/glad.h>

#include "texture.h"

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
    framebuffer(unsigned int width, unsigned int height, framebuffer_type type = framebuffer_type::colour);

    void bind();

    void free()
    {
        glDeleteFramebuffers(1, &m_id);
    }

private:
    unsigned int m_width = 0;
    unsigned int m_height = 0;
    unsigned int m_id = 0;

    framebuffer_type m_type = framebuffer_type::colour;

    std::shared_ptr<texture> m_texture = nullptr;
    unsigned int m_render_buffer_object = 0;
};
}
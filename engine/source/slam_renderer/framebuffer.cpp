#include "framebuffer.h"

#include "renderer.h"

namespace{
    static const float quad_vertices[] = {
        // positions   // texCoords
        -1.0f,  1.0f,  0.0f, 1.0f,
        -1.0f, -1.0f,  0.0f, 0.0f,
         1.0f, -1.0f,  1.0f, 0.0f,

        -1.0f,  1.0f,  0.0f, 1.0f,
         1.0f, -1.0f,  1.0f, 0.0f,
         1.0f,  1.0f,  1.0f, 1.0f
    };
}

namespace slam_renderer
{
framebuffer::framebuffer(unsigned int width, unsigned int height, unsigned int samples, std::shared_ptr<shader> shader, framebuffer_type type)
    : m_type(type)
    , m_width(width)
    , m_height(height)
    , m_samples(samples)
    , m_shader(shader)
{
    glGenFramebuffers(1, &m_id);
    glBindFramebuffer(GL_FRAMEBUFFER, m_id);

    if (m_type < framebuffer_type::no_colour)
    {
        m_texture = renderer::get_instance()->get_register_texture("", false, texture_type::texture_2d, width, height, samples);
        GLenum texture_type = samples > 1 ? GL_TEXTURE_2D_MULTISAMPLE : GL_TEXTURE_2D;
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, texture_type, m_texture->get_id(), 0);
    }

    if (m_type == framebuffer_type::colour_depth_stencil)
    {
        glGenRenderbuffers(1, &m_render_buffer_object);
        glBindRenderbuffer(GL_RENDERBUFFER, m_render_buffer_object);
        if (samples > 1)
        {
            glRenderbufferStorageMultisample(GL_RENDERBUFFER, 4, GL_DEPTH24_STENCIL8, width, height);
        }
        else
        {
            glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, width, height);
        }
        glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, m_render_buffer_object);
        glBindRenderbuffer(GL_RENDERBUFFER, 0);
    }

    if (m_type == framebuffer_type::depth)
    {
        m_texture = renderer::get_instance()->get_register_texture("", false, texture_type::depth_2d, width, height);
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, m_texture->get_id(), 0);
        glDrawBuffer(GL_NONE);
        glReadBuffer(GL_NONE);
    }

    if (int res = glCheckFramebufferStatus(GL_FRAMEBUFFER); res != GL_FRAMEBUFFER_COMPLETE)
    {
        std::cout << "ERROR::FRAMEBUFFER: Creation failed with error: " << res << std::endl;
    }
    else
    {
        std::cout << "FRAMEBUFFER: Created " << m_id << std::endl;
    }

    setup_quad();

    // Create intermediates for sampling
    if (samples > 1)
    {
        glGenFramebuffers(1, &m_sample_id);
        glBindFramebuffer(GL_FRAMEBUFFER, m_sample_id);
        m_sample_texture = renderer::get_instance()->get_register_texture("", false, texture_type::texture_2d, width, height, 1);
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_sample_texture->get_id(), 0);

        if (int res = glCheckFramebufferStatus(GL_FRAMEBUFFER); res != GL_FRAMEBUFFER_COMPLETE)
        {
            std::cout << "ERROR::FRAMEBUFFER: Creation of the intermediate sampling buffer failed with error: " << res << std::endl;
        }
        else
        {
            std::cout << "FRAMEBUFFER: Created " << m_sample_id << std::endl;
        }
    }

    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void framebuffer::setup_quad()
{
    glGenVertexArrays(1, &m_vertex_array);
    glBindVertexArray(m_vertex_array);

    glGenBuffers(1, &m_vertex_buffer);
    glBindBuffer(GL_ARRAY_BUFFER, m_vertex_buffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(quad_vertices), &quad_vertices, GL_STATIC_DRAW);

    // Vertex positions
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // UVs
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));
    glEnableVertexAttribArray(1);

    // Unbind
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void framebuffer::draw(float delta)
{
    bind(true);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glDisable(GL_DEPTH_TEST);
    glClear(GL_COLOR_BUFFER_BIT);
    m_shader->use();
    glBindVertexArray(m_vertex_array);
    glActiveTexture(GL_TEXTURE0);
    if (m_samples > 1)
    {
        m_sample_texture->bind();
    }
    else
    {
        m_texture->bind();
    }
    glDrawArrays(GL_TRIANGLES, 0, 6);

    m_shader->post_draw();
    glEnable(GL_DEPTH_TEST);
}

void framebuffer::bind(bool for_sampling)
{
    // Write to the buffer as normal
    if (!for_sampling || m_samples == 1)
    {
        glBindFramebuffer(GL_FRAMEBUFFER, m_id);
    }
    // Reading requires a downsample first
    else
    {
        glBindFramebuffer(GL_READ_FRAMEBUFFER, m_id);
        glBindFramebuffer(GL_DRAW_FRAMEBUFFER, m_sample_id);
        glBlitFramebuffer(0, 0, m_width, m_height, 0, 0, m_width, m_height, GL_COLOR_BUFFER_BIT, GL_NEAREST);
    }
}
}
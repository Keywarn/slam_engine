#include "framebuffer.h"

#include "renderer.h"

namespace render_engine
{
framebuffer::framebuffer(unsigned int width, unsigned int height, framebuffer_type type)
    : m_type(type)
    , m_width(width)
    , m_height(height)
{
    glGenFramebuffers(1, &m_id);

    m_texture = renderer::get_instance()->get_register_texture("", texture_type::texture_2d, width, height);

    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_texture->get_id(), 0);

    if (m_type == framebuffer_type::depth_stencil)
    {
        glGenRenderbuffers(1, &m_render_buffer_object);
        glBindRenderbuffer(GL_RENDERBUFFER, m_render_buffer_object);
        glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, width, height);
        glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, m_render_buffer_object);
    }

    if (int res = glCheckFramebufferStatus(GL_FRAMEBUFFER); res != GL_FRAMEBUFFER_COMPLETE)
    {
        std::cout << "ERROR::FRAMEBUFFER: Creation failed with error: " << res << std::endl;
    }
    else
    {
        std::cout << "FRAMEBUFFER: Created " << m_id << std::endl;
    }
}

void framebuffer::bind()
{
    glBindFramebuffer(GL_FRAMEBUFFER, m_id);
}
}
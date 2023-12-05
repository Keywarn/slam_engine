#include "mesh.h"

#include <glm/glm/glm.hpp>
#include <glm/glm/gtc/matrix_transform.hpp>

#include "renderer.h"

namespace render_engine
{
mesh::mesh(renderer* renderer, vertices vertices, faces faces, render_engine::shader* shader, glm::mat4 transform)
    : m_renderer(renderer)
    , m_transform(transform)
    , m_vertices(vertices)
    , m_faces(faces)
    , m_shader(shader)
{
    glGenVertexArrays(1, &m_vertex_array);
    glBindVertexArray(m_vertex_array);

    glGenBuffers(1, &m_vertex_buffer);
    glBindBuffer(GL_ARRAY_BUFFER, m_vertex_buffer);
    glBufferData(GL_ARRAY_BUFFER, m_vertices.size() * sizeof(float), &m_vertices.front(), GL_STATIC_DRAW);

    glGenBuffers(1, &m_element_buffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_element_buffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_faces.size() * sizeof(unsigned int), &m_faces.front(), GL_STATIC_DRAW);

    // Co-ords
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    //// Colour
    //glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    //glEnableVertexAttribArray(1);

    // UVs
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    // Unbind
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void mesh::draw(float delta)
{
    //animate first
    m_transform = glm::rotate(m_transform, delta * glm::radians(90.f), glm::vec3(0.5f, 1.0f, 0.0f));

    m_shader->use();
    m_shader->set_mat4("transform", m_transform);
    m_shader->set_mat4("view", m_renderer->get_view());
    m_shader->set_mat4("projection", m_renderer->get_projection());

    glBindVertexArray(m_vertex_array);
    glDrawElements(GL_TRIANGLES, m_faces.size(), GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}

void mesh::free()
{
    glDeleteVertexArrays(1, &m_vertex_array);
    glDeleteBuffers(1, &m_vertex_buffer);
}
}
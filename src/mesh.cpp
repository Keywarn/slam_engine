#include "mesh.h"

namespace renderer
{
mesh::mesh(vertices vertices, faces faces, renderer::shader* shader)
    : m_vertices(vertices)
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
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // Colour
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    // UVs
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);

    // Unbind
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void mesh::draw()
{
    m_shader->use();
    glBindVertexArray(m_vertex_array);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}

void mesh::free()
{
    glDeleteVertexArrays(1, &m_vertex_array);
    glDeleteBuffers(1, &m_vertex_buffer);
}
}
#pragma once

#include <vector>
#include "shader.h"

namespace renderer
{
typedef std::vector<float> vertices;
typedef std::vector<unsigned int> faces;

class mesh
{
public:
    mesh(vertices vertices, faces faces, shader* shader);

    void draw();

    void free();

private:
    vertices m_vertices;
    faces m_faces;

    unsigned int m_vertex_array;
    unsigned int m_vertex_buffer;
    unsigned int m_element_buffer;

    shader* m_shader;
};
}


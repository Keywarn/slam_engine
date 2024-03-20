#pragma once

#include <vector>
#include <glm/glm/glm.hpp>

#include "material.h"

namespace render_engine
{
class renderer;

struct vertex
{
    glm::vec3 m_position;
    glm::vec3 m_normal;
    glm::vec2 m_uv;
};

typedef std::vector<vertex> vertices;
typedef std::vector<unsigned int> faces;

class mesh
{
public:
    mesh(vertices vertices, faces faces, std::shared_ptr<material> material, glm::mat4 transform);

    void draw(float delta, glm::mat4 parent_transform);

    void setup();

    void free();

    void override_material(std::shared_ptr<material> material)
    {
        m_material = material;
    }

private:
    glm::mat4 m_transform;

    vertices m_vertices;
    faces m_faces;

    unsigned int m_vertex_array;
    unsigned int m_vertex_buffer;
    unsigned int m_element_buffer;

    std::shared_ptr<material> m_material;
};
}


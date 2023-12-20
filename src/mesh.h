#pragma once

#include <vector>
#include <glm/glm/glm.hpp>

#include "shader.h"

namespace render_engine
{
class renderer;

typedef std::vector<float> vertices;
typedef std::vector<unsigned int> faces;

typedef std::vector<float> texture_uvs;

class mesh
{
public:
    mesh(renderer* renderer, vertices vertices, faces faces, std::shared_ptr<shader> shader, glm::mat4 transform);

    void draw(float delta);

    void free();

private:
    glm::mat4 m_transform;

    vertices m_vertices;
    faces m_faces;

    unsigned int m_vertex_array;
    unsigned int m_vertex_buffer;
    unsigned int m_element_buffer;

    std::shared_ptr<shader> m_shader;

    renderer* m_renderer;
};
}


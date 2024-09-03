#pragma once

#include "assimp/Importer.hpp"
#include "assimp/scene.h"
#include "assimp/postprocess.h"

#include "mesh.h"

namespace render_engine
{
class model
{
public:
    model(std::string path, glm::mat4 transform, unsigned int shader_index = 0)
        : m_transform(transform)
        , m_shader_index(shader_index)
    {
        load(path);
    }

    void draw(float delta, std::shared_ptr<material> override_material = nullptr);

    void free()
    {
        for (mesh& mesh : m_meshes)
        {
            mesh.free();
        }
    }

    void override_material(std::shared_ptr<material> material)
    {
        for (mesh& mesh : m_meshes)
        {
            mesh.override_material(material);
        }
    }

private:
    void load(std::string path);
    void process_node(aiNode* ai_node, const aiScene* ai_scene);
    mesh process_mesh(aiMesh* ai_mesh, const aiScene* ai_scene);

    // TODO these should probably be node-like and contain child meshes for transforms etc.
    std::vector<mesh> m_meshes;

    std::string m_directory;
    std::string m_name;

    glm::mat4 m_transform;

    unsigned int m_shader_index = 0;
};
}

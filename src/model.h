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
    model(std::string path, glm::mat4 transform)
        : m_transform(transform)
    {
        load(path);
    }

    void draw(float delta);

    void free()
    {
        for (mesh& mesh : m_meshes)
        {
            mesh.free();
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
};
}

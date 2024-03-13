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
    model(char* path)
    {
        load(path);
    }

    void draw(float delta);

private:
    void load(std::string path);
    void process_node(aiNode* ai_node, const aiScene* ai_scene);
    mesh process_mesh(aiMesh* ai_mesh, const aiScene* ai_scene);

    // TODO these should probably be node-like and contain child meshes for transforms etc.
    std::vector<mesh> m_meshes;
};
}

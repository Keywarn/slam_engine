#include "model.h"

#include "renderer.h"

namespace render_engine
{
void model::draw(float delta)
{
    for (unsigned int i = 0; i < m_meshes.size(); ++i)
    {
        m_meshes[i].draw(delta);
    }
}

void model::load(std::string path)
{
    Assimp::Importer importer;
    const aiScene* ai_scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_GenNormals);

    if (!ai_scene || ai_scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !ai_scene->mRootNode)
    {
        std::cout << "ERROR::MODEL::" << importer.GetErrorString() << std::endl;
        return;
    }

    process_node(ai_scene->mRootNode, ai_scene);
}

void model::process_node(aiNode* ai_node, const aiScene* ai_scene)
{
    for (unsigned int i = 0; i < ai_node->mNumMeshes; ++i)
    {
        aiMesh* ai_mesh = ai_scene->mMeshes[ai_node->mMeshes[i]];
        m_meshes.push_back(process_mesh(ai_mesh, ai_scene));
    }

    for (unsigned int i = 0; i < ai_node->mNumChildren; ++i)
    {
        process_node(ai_node->mChildren[i], ai_scene);
    }
}

mesh model::process_mesh(aiMesh* ai_mesh, const aiScene* ai_scene)
{
    vertices vertices;
    faces faces;

    renderer* renderer = renderer::get_instance();

    for (unsigned int i = 0; i < ai_mesh->mNumVertices; ++i)
    {
        vertex vertex;

        vertex.m_position.x = ai_mesh->mVertices[i].x;
        vertex.m_position.y = ai_mesh->mVertices[i].y;
        vertex.m_position.z = ai_mesh->mVertices[i].z;

        vertex.m_normal.x = ai_mesh->mNormals[i].x;
        vertex.m_normal.y = ai_mesh->mNormals[i].y;
        vertex.m_normal.z = ai_mesh->mNormals[i].z;

        if (ai_mesh->HasTextureCoords(0))
        {
            vertex.m_uv.x = ai_mesh->mTextureCoords[0][i].x;
            vertex.m_uv.y = ai_mesh->mTextureCoords[0][i].y;
        }
        else
        {
            vertex.m_uv = glm::vec2(0.f);
        }

        vertices.push_back(vertex);
    }
    
    for (unsigned int i = 0; i < ai_mesh->mNumFaces; ++i)
    {
        aiFace ai_face = ai_mesh->mFaces[i];
        for (unsigned int j = 0; j < ai_face.mNumIndices; ++j)
        {
            faces.push_back(ai_face.mIndices[j]);
        }
    }

    // TODO we should get some kind of default material from the renderer
    std::shared_ptr<material> mesh_material;

    if (ai_mesh->mMaterialIndex >= 0)
    {
        aiMaterial* ai_material = ai_scene->mMaterials[ai_mesh->mMaterialIndex];

        mesh_material = renderer->find_material(ai_material->GetName().C_Str());
        
        //// No material so we create it
        if(mesh_material == nullptr)
        {
            std::shared_ptr<texture> albedo, specular;
            // TODO support mulitple textures of each type per material
            if (ai_material->GetTextureCount(aiTextureType_DIFFUSE) > 0)
            {
                // TODO fetch the texture from the renderer first using the path if possible
                aiString path;
                ai_material->GetTexture(aiTextureType_DIFFUSE, 0, &path);
                albedo = renderer->register_texture(path.C_Str());
            }
            // TODO we just get the shader using a magic number...
            mesh_material = std::make_shared<material>(renderer->get_shader(0), albedo, 32.f, glm::vec3(1.f, 1.f, 1.f), 1.f, 1.f);

            // TODO remove duplicated code here and create a method
            if (ai_material->GetTextureCount(aiTextureType_SPECULAR) > 0)
            {
                // TODO fetch the texture from the renderer first using the path if possible
                aiString path;
                ai_material->GetTexture(aiTextureType_SPECULAR, 0, &path);
                specular = renderer->register_texture(path.C_Str());

                mesh_material->set_specular_map(specular);
            }
        }
    }

    return mesh(vertices, faces, mesh_material, glm::mat4(1.));
}

}
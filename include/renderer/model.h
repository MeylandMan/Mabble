#pragma once
#include<renderer/mesh.h>

#include"assimp/Importer.hpp"
#include"assimp/scene.h"
#include"assimp/postprocess.h"

using namespace std;

class Model
{
public:
    Model(string& path, bool gamma = false, bool negativeY = false) : gammaCorrection(gamma), m_NegativeTexCoordY(negativeY)
    {
        loadModel(path);
    }
 
    void negateTexCoordY(string const& path, bool x) {
        for (unsigned int i = 0; i < meshes.size(); i++)
        {
            for (unsigned int j = 0; j < meshes[i].vertices.size(); j++) {
                meshes[i].vertices[j].TexCoord.y = -meshes[i].vertices[j].TexCoord.y;
           }
        }
        m_NegativeTexCoordY = x;
    }
    /*
    //Delete the copy constructor/assignment.
    Model(const Model&) = delete;
    Model& operator=(const Model&) = delete;

    Model(Model&& other)
    {
        // Delete textures before exiting the program
        for (MeshTexture& texture : textures_loaded) {
            glDeleteTextures(1, &texture.id);
            texture.id = 0;
        }

        textures_loaded.clear();
    }

    Model& operator=(Model&& other)
    {
        //ALWAYS check for self-assignment.
        if (this != &other)
        {
            swap(textures_loaded, other.textures_loaded);
        }
        return *this;
    }
    */

    void Draw(Shader& shader);

    vector<MeshTexture> textures_loaded;
    vector<Mesh>meshes;
    string directory;
    bool gammaCorrection;

private:
    void loadModel(string& path);
    void processNode(aiNode* node, const aiScene* scene);
    Mesh processMesh(aiMesh* mesh, const aiScene* scene);
    vector<MeshTexture> loadMaterialTextures(aiMaterial* mat, aiTextureType type, string typeName);
    unsigned int m_DrawCall;
    bool m_NegativeTexCoordY;
};

void removeBackHash(string& str);

unsigned int TextureFromFile(const char* path, const string& directory, bool gamma = false);
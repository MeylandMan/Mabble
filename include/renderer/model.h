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
    ~Model();
    /*
    
    */
    
    //Delete the copy constructor/assignment.
    Model(const Model&) = delete;
    Model& operator=(const Model&) = delete;

    Model(Model&& other)
    {
        deleteModel();
    }

    Model& operator=(Model&& other)
    {
        //ALWAYS check for self-assignment.
        if (this != &other)
        {
            swap(meshes, other.meshes);
            swap(textures_loaded, other.textures_loaded);
        }
        return *this;
    }
    void Draw(Shader& shader);

    vector<MeshTexture> textures_loaded;
    vector<Mesh>meshes;
    string directory;
    bool gammaCorrection;
    bool m_NegativeTexCoordY = false;
private:
    void loadModel(string& path);
    void deleteModel();
    void processNode(aiNode* node, const aiScene* scene);
    Mesh processMesh(aiMesh* mesh, const aiScene* scene);
    vector<MeshTexture> loadMaterialTextures(aiMaterial* mat, aiTextureType type, string typeName);
    unsigned int m_DrawCall;
};

void removeBackHash(string& str);

unsigned int TextureFromFile(const char* path, const string& directory, bool gamma = false);
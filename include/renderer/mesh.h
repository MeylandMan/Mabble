#pragma once
#include<renderer/Vertex.h>
#include<vector>
#include<renderer/shader.h>
#include<renderer/vao.h>
#include<renderer/vbo.h>
#include<renderer/ibo.h>
#include<renderer/textures.h>
#include<renderer/VertexBufferLayout.h>
#include<string>
#include <algorithm>

using namespace std;

class Mesh {
public:
    Mesh(vector<Vertex>& vertices, vector<unsigned int>& indices, vector<MeshTexture>& textures);

    void setShininess(float x) { m_Shiny = x; }
    float getShininess() { return m_Shiny; }
    void deleteMesh();
    void Draw(Shader& shader);
    void DrawNormals();
public:
    vector<Vertex> vertices;
    vector<float> normals;
    vector<unsigned int> indices;
    vector<MeshTexture> textures;
    unsigned int VAO = 0;
    unsigned int NORMAL_VAO = 0;
protected:
    float shininess;
private:
    float m_Shiny = 32.f;
    unsigned int VBO = 0, EBO = 0;
    unsigned int NORMAL_VBO = 0;
    void setupMesh();
    void setupNormals();
};
#include<renderer/mesh.h>

Mesh::Mesh(vector<Vertex>& vertices, vector<unsigned int>& indices, vector<MeshTexture>& textures)
{
    this->vertices = vertices;
    this->indices = indices;
    this->textures = textures;

    for (Vertex vertex : vertices) {
        float normalScale = 1.f;
        vec3 start = vertex.Position;
        vec3 end = vertex.Position + vertex.Normal * normalScale;
        

        normals.push_back(start.x);
        normals.push_back(start.y);
        normals.push_back(start.z);

        normals.push_back(end.x);
        normals.push_back(end.y);
        normals.push_back(end.z);
    }

    setupNormals();
    setupMesh();
   
}

void Mesh::deleteMesh() {
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
    for (MeshTexture texture : textures) {
        glDeleteTextures(1, &texture.id);
        texture.id = 0;
    }
    
    VAO = VBO = EBO = 0;
}

void Mesh::Draw(Shader& shader)
{
    // bind appropriate textures
    unsigned int diffuseNr = 1;
    unsigned int specularNr = 1;
    unsigned int normalNr = 1;
    unsigned int heightNr = 1;
    for (unsigned int i = 0; i < textures.size(); i++)
    {
        glActiveTexture(GL_TEXTURE0 + i); // active proper texture unit before binding
        // retrieve texture number (the N in diffuse_textureN)
        string number;
        string name = textures[i].type;
        shininess = 0.f;
        if (name == "texture_diffuse") {
            name = "material.diffuse";
            number = std::to_string(diffuseNr++);
        }
        else if (name == "texture_specular") {
            shininess = m_Shiny;
            name = "material.specular";
            number = std::to_string(specularNr++);
        }
        else if (name == "texture_normal") {
            name = "material.normal";
            number = std::to_string(normalNr++);
        }
        else if (name == "texture_height") {
            name = "material.height";
            number = std::to_string(heightNr++);
        }
            

        // now set the sampler to the correct texture unit
        shader.setUniform1i((name + number).c_str(), i);
        shader.setUniform1f("material.shininess", shininess);

        // and finally bind the texture
        glBindTexture(GL_TEXTURE_2D, textures[i].id);
    }
    // draw mesh
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, static_cast<unsigned int>(indices.size()), GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);

    // always good practice to set everything back to defaults once configured.
    for (unsigned int i = 0; i < textures.size(); i++) { glBindTexture(GL_TEXTURE_2D, 0); }
    glActiveTexture(GL_TEXTURE0);
}

void Mesh::setupMesh()
{
    // create buffers/arrays

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);
    // load data into vertex buffers
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    // A great thing about structs is that their memory layout is sequential for all its items.
    // The effect is that we can simply pass a pointer to the struct and it translates perfectly to a glm::vec3/2 array which
    // again translates to 3/2 floats which translates to a byte array.
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);
    
    // set the vertex attribute pointers
    // vertex Positions
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
    // vertex texture coords
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, TexCoord));
    // vertex normals
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Normal));
    // vertex tangent
    glEnableVertexAttribArray(3);
    glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Tangent));
    // vertex bitangent
    glEnableVertexAttribArray(4);
    glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Bitangent));
    // ids
    glEnableVertexAttribArray(5);
    glVertexAttribIPointer(5, 4, GL_INT, sizeof(Vertex), (void*)offsetof(Vertex, m_BoneIDs));

    // weights
    glEnableVertexAttribArray(6);
    glVertexAttribPointer(6, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, m_Weights));
    glBindVertexArray(0);
}

void Mesh::setupNormals() {

    glGenVertexArrays(1, &NORMAL_VAO);
    glGenBuffers(1, &NORMAL_VBO);

    // Bind
    glBindVertexArray(NORMAL_VAO);
    glBindBuffer(GL_ARRAY_BUFFER, NORMAL_VBO);
    glBufferData(GL_ARRAY_BUFFER, normals.size() * sizeof(float), &normals[0], GL_STATIC_DRAW);


    // set the vertex attribute pointers
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

    // Unbind
    glBindVertexArray(0);
}

void Mesh::DrawNormals() {
    glBindVertexArray(NORMAL_VAO);
    glDrawArrays(GL_LINES, 0, normals.size() / 3);
    glBindVertexArray(0);
}
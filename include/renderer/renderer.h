#pragma once

#include <glad/glad.h>
#include <renderer/vao.h>
#include <renderer/vbo.h>
#include <renderer/ibo.h>
#include <renderer/textures.h>
#include <renderer/openglDebug.h>
#include <renderer/shader.h>
#include <renderer/VertexBufferLayout.h>
#include <vector>
#include <renderer/Vertex.h>
#include<renderer/model.h>
#include<string>

class Renderer
{
public:

	void Draw(const vao& va, const ibo& ib, Shader& shader) const;
	void DrawModel(Model& model, Shader& shader) const; 
	void DrawModelNormals(Model& model) const;
	void Clear() const;

private:

};
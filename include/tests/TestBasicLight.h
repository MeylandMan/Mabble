#pragma once

#include "tests/Test.h"

#define DEFAULT_WINDOW_WIDTH 1280
#define DEFAULT_WINDOW_HEIGHT 720
#define DEFAULT_ZNEAR 0.1f
#define DEFAULT_ZFAR 100.0f
#define DEFAULT_FOV 60.0f

namespace test {
	class TestBasicLight : public Test {
	public:
		TestBasicLight();
		~TestBasicLight() { m_Shader.clear(); }

		void onRender(GLFWwindow* window, Renderer renderer, glm::mat4* view, Camera* camera) override;
		void onImGUI() override;
	private:
		float m_Vertices[144] = {
			// POSITION				NORMALS
			-0.5f, -0.5f, -0.5f, 0.0f, 0.0f, 1.0f,
			 0.5f, -0.5f, -0.5f, 0.0f, 0.0f, 1.0f, // FRONT
			 0.5f,  0.5f, -0.5f, 0.0f, 0.0f, 1.0f,
			-0.5f,  0.5f, -0.5f, 0.0f, 0.0f, 1.0f,

			-0.5f, -0.5f,  0.5f, 0.0f, 0.0f, -1.0f,
			 0.5f, -0.5f,  0.5f, 0.0f, 0.0f, -1.0f, // BACK
			 0.5f,  0.5f,  0.5f, 0.0f, 0.0f, -1.0f,
			-0.5f,  0.5f,  0.5f, 0.0f, 0.0f, -1.0f,

			-0.5f, -0.5f, -0.5f, -1.0f, 0.0f, 0.0f,
			-0.5f,  0.5f, -0.5f, -1.0f, 0.0f, 0.0f, // LEFT
			-0.5f,  0.5f,  0.5f, -1.0f, 0.0f, 0.0f,
			-0.5f, -0.5f,  0.5f, -1.0f, 0.0f, 0.0f,

			 0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f,
			 0.5f,  0.5f, -0.5f, 1.0f, 0.0f, 0.0f, // RIGHT
			 0.5f,  0.5f,  0.5f, 1.0f, 0.0f, 0.0f,
			 0.5f, -0.5f,  0.5f, 1.0f, 0.0f, 0.0f,

			-0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f,
			 0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f, // DOWN
			 0.5f, -0.5f,  0.5f, 0.0f, -1.0f, 0.0f,
			-0.5f, -0.5f,  0.5f, 0.0f, -1.0f, 0.0f,

			 0.5f,  0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
			-0.5f,  0.5f, -0.5f, 0.0f, 1.0f, 0.0f, // UP
			-0.5f,  0.5f,  0.5f, 0.0f, 1.0f, 0.0f,
			 0.5f,  0.5f,  0.5f, 0.0f, 1.0f, 0.0f
		};
		unsigned int indices[36] = {
			// front and back
			0, 3, 2,
			2, 1, 0,

			4, 5, 6,
			6, 7 ,4,
			// left and right
			11, 8, 9,
			9, 10, 11,

			12, 13, 14,
			14, 15, 12,
			// bottom and top
			16, 17, 18,
			18, 19, 16,

			20, 21, 22,
			22, 23, 20
		};
		Shader m_Shader;
		VertexBufferLayout m_Layout;
		vbo m_Vbo;
		ibo m_Ibo;
		glm::mat4 m_Projection;

		// Light
		vao m_ObjVao;
		glm::vec4 LightColor;
		glm::vec3 m_LightPosition;
		glm::vec3 m_LightScale;
		glm::vec3 m_LightRotation;
		glm::mat4 m_LightModel;

		float specularStrength;
		float ambiantStrength;
		//Object
		glm::vec4 ObjColor;
		glm::vec3 m_ObjPosition;
		glm::vec3 m_ObjScale;
		glm::vec3 m_ObjRotation;
		glm::mat4 m_ObjModel;

	};

}
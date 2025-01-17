#include "tests/Test.h"

namespace test {
	Testmenu::Testmenu(Test*& currentTestPointer) : m_CurrentTest(currentTestPointer) {

	}

	void Testmenu::onRender(GLFWwindow* window, Renderer renderer, glm::mat4* view, Camera* cam) {

	}

	void Testmenu::onImGUI() {
		for (auto& test : m_Tests) {
			if (ImGui::Button(test.first.c_str())) {
				m_CurrentTest = test.second();
			}
		}
	}

	DefaultTest::DefaultTest() {
		m_Shader.loadShaderProgramFromFile(SHADERS_PATH "Default/vertex.vert", SHADERS_PATH "Default/fragment.frag");
	}

	DefaultTest::~DefaultTest() {
		m_Shader.clear();
	}

	void DefaultTest::onRender(GLFWwindow* window, Renderer renderer, glm::mat4* view, Camera* cam) {
		int WINDOW_WIDTH = 0, WINDOW_HEIGHT = 0;

		glfwGetFramebufferSize(window, &WINDOW_WIDTH, &WINDOW_HEIGHT);

		glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
		glClearColor(0.5f, 0.5f, 0.5f, 1.f);

		m_Projection = glm::perspective(glm::radians(cam->Zoom), (float)WINDOW_WIDTH / (float)WINDOW_HEIGHT, 0.1f, 10000.f);

		m_Shader.bind();
		m_Shader.setUniformMatrix4f("u_View", cam->GetViewMatrix());
		m_Shader.setUniformMatrix4f("u_Proj", m_Projection);

		//Sponza
		{
			glm::mat4 m_SponzaMatrix(1.f);
			//m_SponzaMatrix = glm::scale(m_SponzaMatrix, glm::vec3(0.01f));
			m_Shader.setUniformMatrix4f("u_Model", m_SponzaMatrix);
			m_Shader.setUniform1i("u_NegativeTexCoord", m_SponzaModel.m_NegativeTexCoordY);
			renderer.DrawModel(m_SponzaModel, m_Shader);
		}


	}
	void DefaultTest::onImGUI() {
		ImGui::Text("This is just a test");
	}
}
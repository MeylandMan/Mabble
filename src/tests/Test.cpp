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
		m_DirLight.direction = glm::vec3(0.f, 1.f, 0.f);
		m_DirLight.ambient = VECTOR_ZERO;
		m_DirLight.diffuse = VECTOR_UNIT;
		m_DirLight.specular = VECTOR_UNIT;
		
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

		m_SpotLight.position = cam->Position; 
		m_SpotLight.direction = cam->Front;
		m_SpotLight.ambient = VECTOR_ZERO; 
		m_SpotLight.diffuse = VECTOR_UNIT; 
		m_SpotLight.specular = VECTOR_UNIT;
		m_SpotLight.constant = 1.f; 
		m_SpotLight.linear = 0.09f; 
		m_SpotLight.quadratic = 0.032f;
		m_SpotLight.cutOff = 15.f; 
		m_SpotLight.outerCutOff = 30.f;

		m_Projection = glm::perspective(glm::radians(cam->Zoom), (float)WINDOW_WIDTH / (float)WINDOW_HEIGHT, 0.1f, 10000.f);

		m_Shader.bind();
		m_Shader.setUniformMatrix4f("u_View", cam->GetViewMatrix());
		m_Shader.setUniformMatrix4f("u_Proj", m_Projection);

		//Directional light
		m_Shader.setUniform3f("dirLight.direction", m_DirLight.direction);
		m_Shader.setUniform3f("dirLight.ambient", m_DirLight.ambient);
		m_Shader.setUniform3f("dirLight.diffuse", m_DirLight.diffuse);
		m_Shader.setUniform3f("dirLight.specular", m_DirLight.specular);

		//Camera Spotlight
		m_Shader.setUniform3f("spotLight.position", m_SpotLight.position);
		m_Shader.setUniform3f("spotLight.direction", m_SpotLight.direction);

		m_Shader.setUniform3f("spotLight.ambient", m_SpotLight.ambient);
		m_Shader.setUniform3f("spotLight.diffuse", m_SpotLight.diffuse);
		m_Shader.setUniform3f("spotLight.specular", m_SpotLight.specular);

		m_Shader.setUniform1f("spotLight.constant", m_SpotLight.constant);
		m_Shader.setUniform1f("spotLight.linear", m_SpotLight.linear);
		m_Shader.setUniform1f("spotLight.quadratic", m_SpotLight.quadratic);

		m_Shader.setUniform1f("spotLight.cutOff", m_SpotLight.cutOff);
		m_Shader.setUniform1f("spotLight.outerCutOff", m_SpotLight.outerCutOff);
		//Sponza
		{
			glm::mat4 m_SponzaMatrix(1.f);

			m_SponzaMatrix = glm::translate(m_SponzaMatrix, glm::vec3(0.f));
			m_SponzaMatrix = glm::scale(m_SponzaMatrix, glm::vec3(0.01f));
			m_Shader.setUniformMatrix4f("u_Model", m_SponzaMatrix);
			m_Shader.setUniform1i("u_NegativeTexCoord", m_SponzaModel.m_NegativeTexCoordY);
			renderer.DrawModel(m_SponzaModel, m_Shader);
		}


	}
	void DefaultTest::onImGUI() {
		ImGui::Text("This is just a test");
	}
}
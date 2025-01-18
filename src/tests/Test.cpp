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
		m_DirLight.direction = glm::vec3(0.6f, -0.6f, -0.6f);
		m_DirLight.ambient = VECTOR_ZERO;
		m_DirLight.diffuse = VECTOR_UNIT;
		m_DirLight.specular = VECTOR_UNIT;
		
		m_SponzaModel.m_NegativeTexCoordY = true;

		m_Shader.loadShaderProgramFromFile(SHADERS_PATH "Default/vertex.vert", SHADERS_PATH "Default/fragment.frag");
	}

	DefaultTest::~DefaultTest() {
		m_Shader.clear();
	}
	
	void DefaultTest::onUpdate(float deltaTime) {
		for (unsigned int i = 0; i < 4; i++) {
			m_pointLights[i].linear = 0.09f;
			m_pointLights[i].quadratic = 0.032f;
		}
		m_pointLights[0].is_on = true;
		m_pointLights[0].position = glm::vec3(11.2f, 1.7f, -4.5f);

		m_pointLights[0].ambient = VECTOR_ZERO;
		m_pointLights[0].diffuse = VECTOR_UNIT;
		m_pointLights[0].specular = VECTOR_UNIT;

		m_pointLights[1].is_on = true;
		m_pointLights[1].position = glm::vec3(-12.f, 1.7f, -4.5f);

		m_pointLights[1].ambient = glm::vec3(1.f, 0.f, 0.f);
		m_pointLights[1].diffuse = VECTOR_UNIT;
		m_pointLights[1].specular = VECTOR_UNIT;

		m_pointLights[2].is_on = true;
		m_pointLights[2].position = glm::vec3(-12.f, 1.7f, 4.f);

		m_pointLights[2].ambient = glm::vec3(0.f, 1.f, 0.f);
		m_pointLights[2].diffuse = VECTOR_UNIT;
		m_pointLights[2].specular = VECTOR_UNIT;

		m_pointLights[3].is_on = true;
		m_pointLights[3].position = glm::vec3(11.2f, 1.7f, 4.5f);

		m_pointLights[3].ambient = glm::vec3(0.f, 0.f, 1.f);
		m_pointLights[3].diffuse = VECTOR_UNIT;
		m_pointLights[3].specular = VECTOR_UNIT;
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
		m_SpotLight.cutOff = 12.5f; 
		m_SpotLight.outerCutOff = 15.f;

		m_Projection = glm::perspective(glm::radians(cam->Zoom), (float)WINDOW_WIDTH / (float)WINDOW_HEIGHT, 0.1f, 10000.f);

		m_Shader.bind();
		m_Shader.setUniformMatrix4f("u_View", cam->GetViewMatrix());
		m_Shader.setUniformMatrix4f("u_Proj", m_Projection);
		m_Shader.setUniform3f("u_ViewPosition", cam->Position);

		//Directional light
		m_Shader.setUniform3f("dirLight.direction", m_DirLight.direction);
		m_Shader.setUniform3f("dirLight.ambient", m_DirLight.ambient);
		m_Shader.setUniform3f("dirLight.diffuse", m_DirLight.diffuse);
		m_Shader.setUniform3f("dirLight.specular", m_DirLight.specular);

		//Point Lights
		for (unsigned int i = 0; i < 4; i++) {

			std::string temp = std::format("pointLights[{}].position", i);
			m_Shader.setUniform3f(temp.c_str(), m_pointLights[i].position);
			temp = std::format("pointLights[{}].ambient", i);
			m_Shader.setUniform3f(temp.c_str(), m_pointLights[i].ambient);
			temp = std::format("pointLights[{}].diffuse", i);
			m_Shader.setUniform3f(temp.c_str(), m_pointLights[i].diffuse);
			temp = std::format("pointLights[{}].specular", i);
			m_Shader.setUniform3f(temp.c_str(), m_pointLights[i].specular);
			temp = std::format("pointLights[{}].constant", i);
			m_Shader.setUniform1f(temp.c_str(), m_pointLights[i].constant);
			temp = std::format("pointLights[{}].linear", i);
			m_Shader.setUniform1f(temp.c_str(), m_pointLights[i].linear);
			temp = std::format("pointLights[{}].quadratic", i);
			m_Shader.setUniform1f(temp.c_str(), m_pointLights[i].quadratic);
		}

		//Camera Spotlight
		m_Shader.setUniform3f("spotLight.position", m_SpotLight.position);
		m_Shader.setUniform3f("spotLight.direction", m_SpotLight.direction);

		m_Shader.setUniform3f("spotLight.ambient", m_SpotLight.ambient);
		m_Shader.setUniform3f("spotLight.diffuse", m_SpotLight.diffuse);
		m_Shader.setUniform3f("spotLight.specular", m_SpotLight.specular);

		m_Shader.setUniform1f("spotLight.constant", m_SpotLight.constant);
		m_Shader.setUniform1f("spotLight.linear", m_SpotLight.linear);
		m_Shader.setUniform1f("spotLight.quadratic", m_SpotLight.quadratic);

		m_Shader.setUniform1f("spotLight.cutOff", glm::cos(glm::radians(m_SpotLight.cutOff)));
		m_Shader.setUniform1f("spotLight.outerCutOff", glm::cos(glm::radians(m_SpotLight.outerCutOff)));

		//Sponza
		{
			glm::mat4 m_SponzaMatrix(1.f);

			m_SponzaMatrix = glm::translate(m_SponzaMatrix, glm::vec3(0.f));
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
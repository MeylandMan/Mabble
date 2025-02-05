#pragma once

#include <renderer/renderer.h>
#include <functional>
#include <iostream>

#include <GLFW/glfw3.h>

#include <imgui.h>
#include <backends/imgui_impl_glfw.h>
#include <backends/imgui_impl_opengl3.h>

#include <Camera.h>
#include <renderer/lights.h>

#define VECTOR_ZERO glm::vec3(0.f)
#define VECTOR_UNIT glm::vec3(1.f)

namespace test {
	class Test {
	public:
		Test() {}
		virtual ~Test() {}

		virtual void onUpdate(float deltaTime) {}
		virtual void onRender(GLFWwindow* window, Renderer renderer, glm::mat4* view, Camera* camera) {}
		virtual void onImGUI() {}
	};

	class Testmenu : public Test {
	public:
		Testmenu(Test*& currentTestPointer);

		void onRender(GLFWwindow* window, Renderer renderer, glm::mat4* view, Camera* camera) override;
		void onImGUI() override;

		template<typename T>
		void RegisterTest(const std::string& name) {
			std::cout << "Registering test : " << name << std::endl;

			m_Tests.push_back(std::make_pair(name, []() { return new T; }));
		}

		void clear() {
			m_Tests.clear();
		}

	private:
		Test*& m_CurrentTest;
		std::vector<std::pair<std::string, std::function<Test* ()>>> m_Tests;
	};

	class DefaultTest : public Test {
	public:
		DefaultTest();
		~DefaultTest();

		void onUpdate(float deltaTime) override;
		void onRender(GLFWwindow* window, Renderer renderer, glm::mat4* view, Camera* camera) override;
		void onImGUI() override;
	private:
		//Light Casters
		DirLight m_DirLight;
		SpotLight m_SpotLight;
		PointLight m_pointLights[4];
		static unsgined int s_PointLights = 0;
		static  unsgined int s_SpotLights = 0;

		//string m_SponzaModelPath = RESOURCES_PATH "objects/Sponza/Sponza.gltf";
		//string m_SponzaModelPath = RESOURCES_PATH "objects/Toon Link/Toon Link.obj";
		string m_SponzaModelPath = RESOURCES_PATH "objects/backpack/backpack.obj";
		Model m_SponzaModel = Model(m_SponzaModelPath);
		Shader m_Shader;
		glm::mat4 m_Projection;
	};
}
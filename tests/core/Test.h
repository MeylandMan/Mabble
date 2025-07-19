#pragma once

#include "Base.h"
#include "Timestep.h"

#include <functional>
#include <vector>

#include <imgui.h>

namespace test 
{
	class Test 
	{
	public:
		Test() {}
		virtual ~Test() {}

		virtual void OnUpdate(Timestep ts) {}
		virtual void OnRender() {}
		virtual void OnImGUI() {}
	};

	class Testmenu : public Test 
	{
	public:
		Testmenu(Test*& currentTestPointer) :
			m_CurrentTest(currentTestPointer) {}

		void OnRender() override {};
		void OnImGUI() override 
		{
			for (auto& test : m_Tests) 
			{
				if (ImGui::Button(test.first.c_str())) 
				{
					m_CurrentTest = test.second();
				}
			}
		}
		
		template<typename T>
		void RegisterTest(const std::string& name) 
		{
			LOGGER_TRACE("Registering test : {}", name);
			m_Tests.push_back(std::make_pair(name, []() { return new T; }));
		}

		void clear() 
		{
			m_Tests.clear();
		}

	private:
		Test*& m_CurrentTest;
		std::vector<std::pair<std::string, std::function<Test* ()>>> m_Tests;
	};
}
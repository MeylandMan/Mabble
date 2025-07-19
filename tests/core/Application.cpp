#include "mbtpch.h"
#include "Application.h"

#include <glad/glad.h>

Application* Application::s_Instance = nullptr;

Application::Application(int width, int height, const std::string& title) 
{
	MABBLE_ASSERT(!s_Instance, "Application already exists!");
	s_Instance = this;

	m_Window = Window::Create(WindowProps(title, width, height));
	m_Window->SetEventCallback(MABBLE_BIND_EVENT_FN(Application::OnEvent));

	m_ImGuiLayer = new ImGuiLayer();
	m_ImGuiLayer->OnAttach();

}

void Application::Close()
{
	m_Running = false;
	if (m_ImGuiLayer)
	{
		m_ImGuiLayer->OnDetach();
		delete m_ImGuiLayer;
		m_ImGuiLayer = nullptr;
	}
}

void Application::SubmitToMainThread(const std::function<void()>& function)
{
	std::scoped_lock<std::mutex> lock(m_MainThreadQueueMutex);
	m_MainThreadQueue.emplace_back(function);
}

void Application::OnEvent(Event& e)
{
	EventDispatcher dispatcher(e);
	dispatcher.Dispatch<WindowCloseEvent>(MABBLE_BIND_EVENT_FN(Application::OnWindowClose));
	dispatcher.Dispatch<WindowResizeEvent>(MABBLE_BIND_EVENT_FN(Application::OnWindowResize));

	m_ImGuiLayer->OnEvent(e);
}

void Application::Run() 
{
	while (m_Running)
	{
		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// ImGui Render
		m_ImGuiLayer->Begin();

		ImGui::Begin("Imgui window");
		ImGui::Text("This is just a setup");
		ImGui::End();

		m_ImGuiLayer->End();


		m_Window->OnUpdate();
	}
}

bool Application::OnWindowClose(WindowCloseEvent& e)
{
	m_Running = false;
	return true;
}

bool Application::OnWindowResize(WindowResizeEvent& e)
{

	if (e.GetWidth() == 0 || e.GetHeight() == 0)
	{
		m_Minimized = true;
		return false;
	}

	m_Minimized = false;
	glViewport(0, 0, e.GetWidth(), e.GetHeight());

	return false;
}

void Application::ExecuteMainThreadQueue()
{
	std::scoped_lock<std::mutex> lock(m_MainThreadQueueMutex);

	for (auto& func : m_MainThreadQueue)
		func();

	m_MainThreadQueue.clear();
}
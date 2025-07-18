#include "Window.h"
#include <stdexcept>

Window::Window(int width, int height, const std::string& title)
	: m_Width(width), m_Height(height), m_Title(title), m_Window(nullptr) 
{
	if (!glfwInit())
		throw std::runtime_error("Error while initializing GLFW");

	{
	#ifdef MABBLE_DEBUG
		glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GLFW_TRUE);
	#endif
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

		m_Window = glfwCreateWindow(m_Width, m_Height, m_Title.c_str(), nullptr, nullptr);
	}

	if (!m_Window) {
		glfwTerminate();
		throw std::runtime_error("Error while creating GLFW window");
	}

	glfwSetWindowUserPointer(m_Window, this);

	// Make an OpenGL Context
	glfwMakeContextCurrent(m_Window);
	int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
	if (!status) {
		glfwDestroyWindow(m_Window);
		glfwTerminate();
		throw std::runtime_error("Failed to initialize Glad!");
	}

	glfwSwapInterval(1); // Enable vsync

}

Window::~Window() 
{
	if (m_Window)
		glfwDestroyWindow(m_Window);
	glfwTerminate();
}

void Window::PollEvents() const 
{
	glfwPollEvents();
}

bool Window::ShouldClose() const 
{
	return glfwWindowShouldClose(m_Window);
}

void Window::SwapBuffers() const 
{
	glfwSwapBuffers(m_Window);
}

void Window::SetKeyCallback(GLFWkeyfun callback) 
{
	glfwSetKeyCallback(m_Window, callback);
}

void Window::SetMouseButtonCallback(GLFWmousebuttonfun callback) 
{
	glfwSetMouseButtonCallback(m_Window, callback);
}

void Window::SetCursorPosCallback(GLFWcursorposfun callback) 
{
	glfwSetCursorPosCallback(m_Window, callback);
}

bool Window::IsKeyPressed(int key) const 
{
	return glfwGetKey(m_Window, key) == GLFW_PRESS;
}

bool Window::IsMouseButtonPressed(int button) const 
{
	return glfwGetMouseButton(m_Window, button) == GLFW_PRESS;
}

void Window::GetCursorPosition(double& xpos, double& ypos) const 
{
	glfwGetCursorPos(m_Window, &xpos, &ypos);
}

void Window::SetFramebufferSizeCallback(GLFWframebuffersizefun callback) 
{
	glfwSetFramebufferSizeCallback(m_Window, callback);
}

void Window::SetWindowSizeCallback(GLFWwindowsizefun callback) 
{
	glfwSetWindowSizeCallback(m_Window, callback);
}

void Window::SetWindowCloseCallback(GLFWwindowclosefun callback) 
{
	glfwSetWindowCloseCallback(m_Window, callback);
}
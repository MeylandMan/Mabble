#include "WindowsWindow.h"

#include "core/Input.h"

#include "core/events/ApplicationEvent.h"
#include "core/events/MouseEvent.h"
#include "core/events/KeyEvent.h"

#include <glad/glad.h>

namespace Nanonite {

	static uint8_t s_GLFWWindowCount = 0;

	static void GLFWErrorCallback(int error, const char* description)
	{
		LOGGER_CORE_ERROR("GLFW Error ({0}): {1}", error, description);
	}

	WindowsWindow::WindowsWindow(const WindowProps& props)
	{
		Init(props);
	}

	WindowsWindow::~WindowsWindow()
	{
		Shutdown();
	}

	void WindowsWindow::Init(const WindowProps& props)
	{
		m_Data.Title = props.Title;
		m_Data.Width = props.Width;
		m_Data.Height = props.Height;

		LOGGER_CORE_INFO("Creating window {0} ({1}, {2})", props.Title, props.Width, props.Height);

		if (s_GLFWWindowCount == 0)
		{
			NT_PROFILE_SCOPE("glfwInit");
			int success = glfwInit();
			NT_CORE_ASSERT(success, "Could not initialize GLFW!");
			glfwSetErrorCallback(GLFWErrorCallback);
		}

		{
#if defined(MABBLE_DEBUG)
			if (Renderer::GetAPI() == RendererAPI::API::OpenGL)
				glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GLFW_TRUE);
#endif
			m_Window = glfwCreateWindow((int)props.Width, (int)props.Height, m_Data.Title.c_str(), nullptr, nullptr);
			++s_GLFWWindowCount;
		}


		// Initialize Graphic API context
		m_Context = GraphicsContext::Create(m_Window);
		m_Context->Init();

		glfwSetWindowUserPointer(m_Window, &m_Data);
		SetVSync(true);
		SetCursorMode(props.cursorMode);
		SetWindowMode(props.Mode);

		// Set GLFW callbacks
		glfwSetWindowSizeCallback(m_Window, [](GLFWwindow* window, int width, int height)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
				data.Width = width;
				data.Height = height;

				auto event = std::make_shared<WindowResizeEvent>(width, height);
				data.EventCallback(event);
			});

		glfwSetWindowCloseCallback(m_Window, [](GLFWwindow* window)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

				auto event = std::make_shared<WindowCloseEvent>();
				data.EventCallback(event);
			});

		glfwSetKeyCallback(m_Window, [](GLFWwindow* window, int key, int scancode, int action, int mods)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

				switch (action)
				{
				case GLFW_PRESS:
				{
					auto event = Nanonite::CreateRef<KeyPressedEvent>(key, 0);
					data.EventCallback(event);
					break;
				}
				case GLFW_RELEASE:
				{
					auto event = Nanonite::CreateRef<KeyReleasedEvent>(key);
					data.EventCallback(event);
					break;
				}
				case GLFW_REPEAT:
				{
					auto event = Nanonite::CreateRef<KeyPressedEvent>(key, true);
					data.EventCallback(event);
					break;
				}
				}
			});

		glfwSetCharCallback(m_Window, [](GLFWwindow* window, unsigned int keycode)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

				auto event = Nanonite::CreateRef<KeyTypedEvent>(keycode);
				data.EventCallback(event);
			});

		glfwSetMouseButtonCallback(m_Window, [](GLFWwindow* window, int button, int action, int mods)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

				switch (action)
				{
				case GLFW_PRESS:
				{
					auto event = Nanonite::CreateRef<MouseButtonPressedEvent>(button);
					data.EventCallback(event);
					break;
				}
				case GLFW_RELEASE:
				{
					auto event = Nanonite::CreateRef<MouseButtonReleasedEvent>(button);
					data.EventCallback(event);
					break;
				}
				}
			});

		glfwSetScrollCallback(m_Window, [](GLFWwindow* window, double xOffset, double yOffset)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

				auto event = Nanonite::CreateRef<MouseScrolledEvent>((float)xOffset, (float)yOffset);
				data.EventCallback(event);
			});

		glfwSetCursorPosCallback(m_Window, [](GLFWwindow* window, double xPos, double yPos)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

				auto event = Nanonite::CreateRef<MouseMovedEvent>((float)xPos, (float)yPos);
				data.EventCallback(event);
			});

	}

	void WindowsWindow::Shutdown()
	{
		NT_PROFILE_FUNCTION();

		glfwDestroyWindow(m_Window);
		--s_GLFWWindowCount;

		if (s_GLFWWindowCount == 0)
		{
			glfwTerminate();
		}
	}

	void WindowsWindow::OnUpdate()
	{
		NT_PROFILE_FUNCTION();

		glfwPollEvents();
		m_Context->SwapBuffers();

	}

	void WindowsWindow::SetVSync(bool enabled)
	{
		NT_PROFILE_FUNCTION();

		if (enabled)
			glfwSwapInterval(1);
		else
			glfwSwapInterval(0);

		m_Data.VSync = enabled;
	}

	bool WindowsWindow::IsVSync() const
	{
		return m_Data.VSync;
	}

	void WindowsWindow::SetCursorMode(CursorMode mode) {
		m_Data.cursorMode = mode;
		switch (mode) {
		case CursorMode::Normal:
			glfwSetInputMode(m_Window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
			break;
		case CursorMode::Captured:
			glfwSetInputMode(m_Window, GLFW_CURSOR, GLFW_CURSOR_CAPTURED);
			break;
		case CursorMode::Hidden:
			glfwSetInputMode(m_Window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
			break;
		case CursorMode::Disabled:
			glfwSetInputMode(m_Window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
			break;
		default:
			LOGGER_CORE_WARN("Unknown cursor mode: {0}", (int)mode);
			glfwSetInputMode(m_Window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
			break;
		}
	}
	void WindowsWindow::SetWindowMode(WindowMode mode) {
		m_Data.Mode = mode;

		GLFWmonitor* monitor = glfwGetPrimaryMonitor();
		const GLFWvidmode* videoMode = glfwGetVideoMode(monitor);
		int screenWidth = videoMode->width;
		int screenHeight = videoMode->height;

		int xpos = (screenWidth - m_Data.Width) / 2;
		int ypos = (screenHeight - m_Data.Height) / 2;

		switch (mode) {
		case WindowMode::Windowed:
			glfwSetWindowMonitor(m_Window, nullptr, xpos, ypos, m_Data.Width, m_Data.Height, 0);
			break;
		case WindowMode::Fullscreen:
			glfwSetWindowMonitor(m_Window, monitor, 0, 0, m_Data.Width, m_Data.Height, 0);
			break;
		case WindowMode::Borderless:
			glfwSetWindowMonitor(m_Window, nullptr, 0, 0, screenWidth, screenHeight, 0);
			break;
		default:
			LOGGER_CORE_WARN("Unknown window mode: {0}", (int)mode);
			glfwSetWindowMonitor(m_Window, nullptr, 0, 0, m_Data.Width, m_Data.Height, 0);
			break;
		}
	}

	CursorMode WindowsWindow::GetCursorMode() const {
		return m_Data.cursorMode;
	}

	WindowMode WindowsWindow::GetWindowMode() const {
		return m_Data.Mode;
	}

}
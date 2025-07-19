#pragma once

#include "core/Window.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

class WindowsWindow : public Window
{
public:
	WindowsWindow(const WindowProps& props);
	virtual ~WindowsWindow();

	void OnUpdate() override;

	unsigned int GetWidth() const override { return m_Data.Width; }
	unsigned int GetHeight() const override { return m_Data.Height; }

	// Window attributes
	void SetEventCallback(const EventCallbackFn& callback) override { m_Data.EventCallback = callback; }
	void SetVSync(bool enabled) override;
	bool IsVSync() const override;

	virtual void SetCursorMode(CursorMode mode) override;
	virtual void SetWindowMode(WindowMode mode) override;
	virtual CursorMode GetCursorMode() const override;
	virtual WindowMode GetWindowMode() const override;

	virtual void* GetNativeWindow() const { return m_Window; }
private:
	virtual void Init(const WindowProps& props);
	virtual void Shutdown();
private:
	GLFWwindow* m_Window;

	struct WindowData
	{
		std::string Title;
		unsigned int Width, Height;
		bool VSync;
		WindowMode Mode;
		CursorMode cursorMode;
		EventCallbackFn EventCallback;
	};

	WindowData m_Data;
};
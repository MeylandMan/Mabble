#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <string>

class Window
{
public:
	Window(int width, int height, const std::string& title);
	~Window();

	void PollEvents() const;
	bool ShouldClose() const;
	void SwapBuffers() const;

	int GetWidth() const { return m_Width; }
	int GetHeight() const { return m_Height; }
	GLFWwindow* GetNativeWindow() const { return m_Window; }

public:

	void SetKeyCallback(GLFWkeyfun callback);
	void SetMouseButtonCallback(GLFWmousebuttonfun callback);
	void SetCursorPosCallback(GLFWcursorposfun callback);
	void SetFramebufferSizeCallback(GLFWframebuffersizefun callback);
	void SetWindowSizeCallback(GLFWwindowsizefun callback);
	void SetWindowCloseCallback(GLFWwindowclosefun callback);

	bool IsKeyPressed(int key) const;
	bool IsMouseButtonPressed(int button) const;
	void GetCursorPosition(double& xpos, double& ypos) const;

private:
	int m_Width;
	int m_Height;
	std::string m_Title;
	GLFWwindow* m_Window;
};
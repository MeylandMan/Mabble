#include "mbtpch.h"
#include "core/Input.h"

#include "core/Application.h"
#include <GLFW/glfw3.h>


void Input::Init() {
	for (KeyCode code = Key::Space; code <= Key::Menu; ++code)
	{
		s_KeyState[code] = Key::None;
	}
}
	
void Input::OnUpdate() {
	auto* window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());

	for (auto& pair : s_KeyState) {
		KeyCode key = pair.first;
		KeyAction& action = pair.second;

		int state = glfwGetKey(window, static_cast<int32_t>(key));
		bool isPressed = (state == GLFW_PRESS);

		if (isPressed) {
			if (action == Key::None || action == Key::Released)
				action = Key::Pressed;
			else
				action = Key::Held;
		} else {
			if (action == Key::Pressed || action == Key::Held)
				action = Key::Released;
			else
				action = Key::None;
		}
	}
}
	
bool Input::IsKeyPressed(const KeyCode key)
{
	return s_KeyState[key] == Key::Held;
}

bool Input::IsKeyReleased(const KeyCode key)
{
	return s_KeyState[key] == Key::Released;
}

bool Input::IsKeyJustPressed(const KeyCode key)
{
	return s_KeyState[key] == Key::Pressed;
}

bool Input::IsMouseButtonPressed(const MouseCode button)
{
	auto* window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
	auto state = glfwGetMouseButton(window, static_cast<int32_t>(button));
	return state == GLFW_PRESS;
}
	
glm::vec2 Input::GetMousePosition()
{
	auto* window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
	double xpos, ypos;
	glfwGetCursorPos(window, &xpos, &ypos);

	return { (float)xpos, (float)ypos };
}

float Input::GetMouseX()
{
	return GetMousePosition().x;
}

float Input::GetMouseY()
{
	return GetMousePosition().y;
}
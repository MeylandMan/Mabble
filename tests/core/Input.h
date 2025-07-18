#pragma once

#include "KeyCodes.h"
#include "MouseCodes.h"

#include <glm/glm.hpp>
#include <unordered_map>

static std::unordered_map<KeyCode, KeyAction> s_KeyState;

class Input
{
public:
	static void Init();
	static void OnUpdate();
	static bool IsKeyPressed(KeyCode key);
	static bool IsKeyJustPressed(KeyCode key);
	static bool IsKeyReleased(KeyCode key);

	static bool IsMouseButtonPressed(MouseCode button);
	//static bool IsMouseButtonJustPressed(MouseCode button);

	static glm::vec2 GetMousePosition();
	static float GetMouseX();
	static float GetMouseY();
};
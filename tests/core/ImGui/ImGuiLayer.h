#pragma once

#include "core/events/ApplicationEvent.h"
#include "core/events/KeyEvent.h"
#include "core/events/MouseEvent.h"

#include <imgui.h>
#include <imgui_internal.h>

#include <backends/imgui_impl_glfw.h>
#include <backends/imgui_impl_opengl3.h>

class ImGuiLayer
{
public:
	ImGuiLayer() {};
	~ImGuiLayer() = default;

	void OnAttach();
	void OnDetach();
	void OnEvent(Event& e);

	void Begin();
	void End();

	void BlockEvents(bool block) { m_BlockEvents = block; }

	void SetDarkThemeColors();

	uint32_t GetActiveWidgetID() const;
private:
	bool m_BlockEvents = true;
};
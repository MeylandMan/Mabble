#pragma once

#include <functional>

#include "events/Event.h"

enum class CursorMode {
	Normal = 0,
	Captured,
	Hidden,
	Disabled
};

enum class WindowMode {

	Windowed = 0,
	Fullscreen,
	Borderless

};

struct WindowProps {
	std::string Title;
	uint32_t Width;
	uint32_t Height;
	CursorMode cursorMode;
	WindowMode Mode;

	WindowProps(const std::string& title = "Untitled",
		uint32_t width = 1280,
		uint32_t height = 720,
		CursorMode cursorMode = CursorMode::Normal,
		WindowMode mode = WindowMode::Windowed
	)
		: Title(title), Width(width), Height(height), cursorMode(cursorMode), Mode(mode) {
	}
};

// Interface representing a desktop system based Window
class Window {
public:
	using EventCallbackFn = std::function<void(std::shared_ptr<Event>)>;

	virtual ~Window() {}

	virtual void OnUpdate() = 0;

	virtual uint32_t GetWidth() const = 0;
	virtual uint32_t GetHeight() const = 0;


	// Window attributes
	virtual void SetEventCallback(const EventCallbackFn& callback) = 0;
	virtual void SetVSync(bool enabled) = 0;
	virtual bool IsVSync() const = 0;

	virtual void SetCursorMode(CursorMode mode) = 0;
	virtual void SetWindowMode(WindowMode mode) = 0;
	virtual CursorMode GetCursorMode() const = 0;
	virtual WindowMode GetWindowMode() const = 0;

	virtual void* GetNativeWindow() const = 0;

	static std::unique_ptr<Window> Create(const WindowProps& props = WindowProps());
};
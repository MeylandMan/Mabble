#include "mbtpch.h"
#include "Window.h"
#include "Platforms.h"

#ifdef _PLATFORM_WINDOWS_
	#include "platforms/win32/WindowsWindow.h"
#endif

std::unique_ptr<Window> Window::Create(const WindowProps& props)
{
#ifdef _PLATFORM_WINDOWS_
	return std::make_unique<WindowsWindow>(props);
#else
	_ASSERT(false, "Unknown platform!");
	return nullptr;
#endif
}
#include "mbtpch.h"
#include "Window.h"
#include "Platforms.h"

#ifdef MABBLE_PLATFORM_WINDOWS
	#include "platforms/win32/WindowsWindow.h"
#endif

std::unique_ptr<Window> Window::Create(const WindowProps& props)
{
#ifdef MABBLE_PLATFORM_WINDOWS
	return std::make_unique<WindowsWindow>(props);
#else
	MABBLE_ASSERT(false, "Unknown platform!");
	return nullptr;
#endif
}
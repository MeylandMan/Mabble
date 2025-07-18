#include "Window.h"
#include "Platforms.h"

#ifdef MABBLE_PLATFORM_WINDOWS
	#include "Platform/Windows/WindowsWindow.h"
#endif

std::unique_ptr<Window> Window::Create(const WindowProps& props)
{
#ifdef MABBLE_PLATFORM_WINDOWS
	return std::make_unique<WindowsWindow>(props);
#else
	// To replace with ASSERT or similar error handling
	#error "Unknown platform!"
	return nullptr;
#endif
}
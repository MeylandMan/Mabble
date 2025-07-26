#include "Platforms.h"

#include <memory>

#if defined(_DEBUG_BUILD_)
	#if defined(_PLATFORM_WINDOWS_)
		#define _DEBUGBREAK() __debugbreak()
	#elif defined(_PLATFORM_LINUX_)
		#include <signal.h>
		#define _DEBUGBREAK() raise(SIGTRAP)
	#else
		#error "Platform doesn't support debugbreak yet!"
	#endif
		#define _ENABLE_ASSERTS
	#else
		#define _DEBUGBREAK()
#endif

#define BIT(x) (1 << x)

#define MABBLE_BIND_EVENT_FN(fn) [this](auto&&... args) -> decltype(auto) { return this->fn(std::forward<decltype(args)>(args)...); }

#define GLAD_GL_IMPLEMENTATION

#include "debug/Logger.h"
#include "Assert.h"
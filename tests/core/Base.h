#include "Platforms.h"

#include <memory>

#ifdef MABBLE_DEBUG
	#ifdef MABBLE_PLATFORM_WINDOWS
		#define MABBLE_DEBUGBREAK() __debugbreak()
	#elif defined(MABBLE_PLATFORM_LINUX)
		#include <signal.h>
		#define MABBLE_DEBUGBREAK() raise(SIGTRAP)
	#else
		#error "Platform doesn't support debugbreak yet!"
	#endif
		#define MABBLE_ENABLE_ASSERTS
	#else
		#define MABBLE_DEBUGBREAK()
#endif

#define MABBLE_EXPAND_MACRO(x) x
#define MABBLE_STRINGIFY_MACRO(x) #x

#define BIT(x) (1 << x)

#define MABBLE_BIND_EVENT_FN(fn) [this](auto&&... args) -> decltype(auto) { return this->fn(std::forward<decltype(args)>(args)...); }

#define GLAD_GL_IMPLEMENTATION

#include "debug/Logger.h"
#include "Assert.h"
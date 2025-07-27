#pragma once

#include "Base.h"
#include "debug/Logger.h"

#include <filesystem>

#ifdef _ENABLE_ASSERTS
	#define _EXPAND_MACRO(x) x
	#define _STRINGIFY_MACRO(x) #x

	// Alteratively we could use the same "default" message for both "WITH_MSG" and "NO_MSG" and
	// provide support for custom formatting by concatenating the formatting string instead of having the format inside the default message
	#define _INTERNAL_ASSERT_IMPL(type, check, msg, ...) { if(!(check)) { LOGGER_ERROR(msg, __VA_ARGS__); _DEBUGBREAK(); } }
	#define _INTERNAL_ASSERT_WITH_MSG(type, check, ...) _INTERNAL_ASSERT_IMPL(type, check, "Assertion failed: {0}", __VA_ARGS__)
	#define _INTERNAL_ASSERT_NO_MSG(type, check) _INTERNAL_ASSERT_IMPL(type, check, "Assertion '{0}' failed at {1}:{2}", _STRINGIFY_MACRO(check), std::filesystem::path(__FILE__).filename().string(), __LINE__)

	#define _INTERNAL_ASSERT_GET_MACRO_NAME(arg1, arg2, macro, ...) macro
	#define _INTERNAL_ASSERT_GET_MACRO(...) _EXPAND_MACRO( _INTERNAL_ASSERT_GET_MACRO_NAME(__VA_ARGS__, _INTERNAL_ASSERT_WITH_MSG, _INTERNAL_ASSERT_NO_MSG) )

	// Currently accepts at least the condition and one additional parameter (the message) being optional
	#define _ASSERT(...) _EXPAND_MACRO( _INTERNAL_ASSERT_GET_MACRO(__VA_ARGS__)(_, __VA_ARGS__) )
#else
	#define _ASSERT(...)
#endif
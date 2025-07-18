#pragma once

#include "Base.h"
#include "debug/Logger.h"

#include <filesystem>

#ifdef MABBLE_ENABLE_ASSERTS
	// Alteratively we could use the same "default" message for both "WITH_MSG" and "NO_MSG" and
	// provide support for custom formatting by concatenating the formatting string instead of having the format inside the default message
	#define MABBLE_INTERNAL_ASSERT_IMPL(type, check, msg, ...) { if(!(check)) { LOGGER_ERROR(msg, __VA_ARGS__); MABBLE_DEBUGBREAK(); } }
	#define MABBLE_INTERNAL_ASSERT_WITH_MSG(type, check, ...) MABBLE_INTERNAL_ASSERT_IMPL(type, check, "Assertion failed: {0}", __VA_ARGS__)
	#define MABBLE_INTERNAL_ASSERT_NO_MSG(type, check) MABBLE_INTERNAL_ASSERT_IMPL(type, check, "Assertion '{0}' failed at {1}:{2}", MABBLE_STRINGIFY_MACRO(check), std::filesystem::path(__FILE__).filename().string(), __LINE__)

	#define MABBLE_INTERNAL_ASSERT_GET_MACRO_NAME(arg1, arg2, macro, ...) macro
	#define MABBLE_INTERNAL_ASSERT_GET_MACRO(...) MABBLE_EXPAND_MACRO( MABBLE_INTERNAL_ASSERT_GET_MACRO_NAME(__VA_ARGS__, MABBLE_INTERNAL_ASSERT_WITH_MSG, MABBLE_INTERNAL_ASSERT_NO_MSG) )

	// Currently accepts at least the condition and one additional parameter (the message) being optional
	#define MABBLE_ASSERT(...) MABBLE_EXPAND_MACRO( MABBLE_INTERNAL_ASSERT_GET_MACRO(__VA_ARGS__)(_, __VA_ARGS__) )
#else
	#define MABBLE_ASSERT(...)
	#define MABBLE_CORE_ASSERT(...)
#endif
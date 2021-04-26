#pragma once

#include "Hydron/Core/Base.h"
#include "Hydron/Core/Log.h"

#include <filesystem>

#define HYDRON_EXPAND_MACRO(x) x
#define HYDRON_STRINGIFY_MACRO(x) #x
#define HYDRON_ENABLE_ASSERTS

#ifdef HYDRON_ENABLE_ASSERTS

	// Alteratively we could use the same "default" message for both "WITH_MSG" and "NO_MSG" and
	// provide support for custom formatting by concatenating the formatting string instead of having the format inside the default message
	#define HYDRON_INTERNAL_ASSERT_IMPL(type, check, msg, ...) { if(!(check)) { HYDRON##type##ERROR(msg, __VA_ARGS__); HYDRON_DEBUGBREAK(); } }
	#define HYDRON_INTERNAL_ASSERT_WITH_MSG(type, check, ...) HYDRON_INTERNAL_ASSERT_IMPL(type, check, "Assertion failed: {0}", __VA_ARGS__)
	#define HYDRON_INTERNAL_ASSERT_NO_MSG(type, check) HYDRON_INTERNAL_ASSERT_IMPL(type, check, "Assertion '{0}' failed at {1}:{2}", HYDRON_STRINGIFY_MACRO(check), std::filesystem::path(__FILE__).filename().string(), __LINE__)

	#define HYDRON_INTERNAL_ASSERT_GET_MACRO_NAME(arg1, arg2, macro, ...) macro
	#define HYDRON_INTERNAL_ASSERT_GET_MACRO(...) HYDRON_EXPAND_MACRO( HYDRON_INTERNAL_ASSERT_GET_MACRO_NAME(__VA_ARGS__, HYDRON_INTERNAL_ASSERT_WITH_MSG, HYDRON_INTERNAL_ASSERT_NO_MSG) )

	// Currently accepts at least the condition and one additional parameter (the message) being optional
	#define HYDRON_ASSERT(...) HYDRON_EXPAND_MACRO( HYDRON_INTERNAL_ASSERT_GET_MACRO(__VA_ARGS__)(_, __VA_ARGS__) )
	#define HYDRON_CORE_ASSERT(...) HYDRON_EXPAND_MACRO( HYDRON_INTERNAL_ASSERT_GET_MACRO(__VA_ARGS__)(_CORE_, __VA_ARGS__) )
#else
	#define HYDRON_ASSERT(...)
	#define HYDRON_CORE_ASSERT(...)
#endif
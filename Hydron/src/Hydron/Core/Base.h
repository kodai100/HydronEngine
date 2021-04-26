#pragma once

#pragma once

#include <memory>

#include "Hydron/Core/PlatformDetection.h"

#ifdef HYDRON_PLATFORM_WINDOWS
	#ifdef HYDRON_BUILD_DLL
		#define HYDRON_API __declspec(dllexport)
	#else
		#define HYDRON_API __declspec(dllimport)
	#endif
#else
	#error Hydron only support windows !
#endif

#ifdef HYDRON_DEBUG
	#if defined(HYDRON_PLATFORM_WINDOWS)
		#define HYDRON_DEBUGBREAK() __debugbreak()
	#elif defined(HYDRON_PLATFORM_LINUX)
		#include <signal.h>
		#define HYDRON_DEBUGBREAK() raise(SIGTRAP)
	#else
		#error "Platform doesn't support debugbreak yet!"
	#endif
	
	#define HYDRON_ENABLE_ASSERTS
#else
	#define HYDRON_DEBUGBREAK()
#endif

#define HYDRON_EXPAND_MACRO(x) x
#define HYDRON_STRINGIFY_MACRO(x) #x

#define BIT(x) (1 << x)

#define HYDRON_BIND_EVENT_FN(fn) [this](auto&&... args) -> decltype(auto) { return this->fn(std::forward<decltype(args)>(args)...); }

namespace Hazel {

	template<typename T>
	using Scope = std::unique_ptr<T>;
	template<typename T, typename ... Args>
	constexpr Scope<T> CreateScope(Args&& ... args)
	{
		return std::make_unique<T>(std::forward<Args>(args)...);
	}

	template<typename T>
	using Ref = std::shared_ptr<T>;
	template<typename T, typename ... Args>
	constexpr Ref<T> CreateRef(Args&& ... args)
	{
		return std::make_shared<T>(std::forward<Args>(args)...);
	}

}

#include "Hydron/Core/Log.h"
#include "Hydron/Core/Assert.h"
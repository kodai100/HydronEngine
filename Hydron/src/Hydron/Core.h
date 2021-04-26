#pragma once

#ifdef HYDRON_PLATFORM_WINDOWS
	#ifdef HYDRON_BUILD_DLL
		#define HYDRON_API __declspec(dllexport)
	#else
		#define HYDRON_API __declspec(dllimport)
	#endif
#else
	#error Hydron only support windows !
#endif

#define BIT(x) (1 << x)
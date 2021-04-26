#pragma once

#include <memory>

#include "Core.h"
#include "spdlog/spdlog.h"
#include "spdlog/fmt/ostr.h"

namespace Hydron {

	class HYDRON_API Log
	{
	public:
		static void Init();

		inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
		inline static std::shared_ptr<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }

	private:
		static std::shared_ptr<spdlog::logger> s_CoreLogger;
		static std::shared_ptr<spdlog::logger> s_ClientLogger;

	};

}

// Core log macros
#define HYDRON_CORE_TRACE(...)	::Hydron::Log::GetCoreLogger()->trace(__VA_ARGS__);
#define HYDRON_CORE_INFO(...)	::Hydron::Log::GetCoreLogger()->info(__VA_ARGS__);
#define HYDRON_CORE_WARN(...)	::Hydron::Log::GetCoreLogger()->warn(__VA_ARGS__);
#define HYDRON_CORE_ERROR(...)	::Hydron::Log::GetCoreLogger()->error(__VA_ARGS__);
#define HYDRON_CORE_FATAL(...)	::Hydron::Log::GetCoreLogger()->fatal(__VA_ARGS__);

// Client log macros
#define HYDRON_TRACE(...)		::Hydron::Log::GetClientLogger()->trace(__VA_ARGS__);
#define HYDRON_INFO(...)		::Hydron::Log::GetClientLogger()->info(__VA_ARGS__);
#define HYDRON_WARN(...)		::Hydron::Log::GetClientLogger()->warn(__VA_ARGS__);
#define HYDRON_ERROR(...)		::Hydron::Log::GetClientLogger()->error(__VA_ARGS__);
#define HYDRON_FATAL(...)		::Hydron::Log::GetClientLogger()->fatal(__VA_ARGS__);

// if dist build
// #define HYDRON_CORE_INFO
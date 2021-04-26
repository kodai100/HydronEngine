#include "pch.h"

#include "spdlog/sinks/stdout_color_sinks.h"


namespace Hydron {

	std::shared_ptr<spdlog::logger> Log::s_CoreLogger;
	std::shared_ptr<spdlog::logger> Log::s_ClientLogger;


	void Log::Init() {

		spdlog::set_pattern("%^[%T] %n: %v%$");	// [Timestamp] Name: message

		s_CoreLogger = spdlog::stdout_color_mt("HYDRON");
		s_CoreLogger->set_level(spdlog::level::trace);

		s_ClientLogger = spdlog::stdout_color_mt("APP");
		s_ClientLogger->set_level(spdlog::level::trace);

		HYDRON_CORE_WARN("Initialized Log System.");
	}

}
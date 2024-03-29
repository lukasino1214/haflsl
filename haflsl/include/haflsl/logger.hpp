#pragma once

#include <memory>
#include <spdlog/spdlog.h>
#include <spdlog/fmt/ostr.h>

namespace HAFLSL {
	class Log {
	public:
		static void Init();

		static std::shared_ptr<spdlog::logger>& GetLogger() { return s_Logger; }
	private:
		static std::shared_ptr<spdlog::logger> s_Logger;
	};

}

// Core log macros
#define TRACE(...)    if(::HAFLSL::Log::GetLogger()) { ::HAFLSL::Log::GetLogger()->trace(__VA_ARGS__); }
#define INFO(...)     if(::HAFLSL::Log::GetLogger()) { ::HAFLSL::Log::GetLogger()->info(__VA_ARGS__); }
#define WARN(...)     if(::HAFLSL::Log::GetLogger()) { ::HAFLSL::Log::GetLogger()->warn(__VA_ARGS__); }
#define ERROR(...)    if(::HAFLSL::Log::GetLogger()) { ::HAFLSL::Log::GetLogger()->error(__VA_ARGS__); }
#define CRITICAL(...) if(::HAFLSL::Log::GetLogger()) { ::HAFLSL::Log::GetLogger()->critical(__VA_ARGS__); }
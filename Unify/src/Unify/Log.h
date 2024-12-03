#pragma once

#include "Core.h"
#include "spdlog/spdlog.h"
#include <memory>

namespace Unify {
	class UNIFY_API Log
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

// Core logging macros

#define UN_CORE_TRACE(...)	::Unify::Log::GetCoreLogger()->trace(__VA_ARGS__);
#define UN_CORE_INFO(...)	::Unify::Log::GetCoreLogger()->info(__VA_ARGS__);
#define UN_CORE_WARN(...)	::Unify::Log::GetCoreLogger()->warn(__VA_ARGS__);
#define UN_CORE_ERROR(...)	::Unify::Log::GetCoreLogger()->error(__VA_ARGS__);
#define UN_CORE_FATAL(...)	::Unify::Log::GetCoreLogger()->fatal(__VA_ARGS__);

// Client logging macros

#define UN_TRACE(...)	::Unify::Log::GetClientLogger()->trace(__VA_ARGS__);
#define UN_INFO(...)	::Unify::Log::GetClientLogger()->info(__VA_ARGS__);
#define UN_WARN(...)	::Unify::Log::GetClientLogger()->warn(__VA_ARGS__);
#define UN_ERROR(...)	::Unify::Log::GetClientLogger()->error(__VA_ARGS__);
#define UN_FATAL(...)	::Unify::Log::GetClientLogger()->fatal(__VA_ARGS__);
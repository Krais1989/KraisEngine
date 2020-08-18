#pragma once

#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_color_sinks.h>

namespace KE::Log {

	typedef std::shared_ptr<spdlog::logger> spLogger;

	extern spLogger s_coreLogger;
	extern spLogger s_clientLogger;
	extern void Init();
}

#if defined(KE_TEST)

	#define KE_CORE_TRACE(msg, ...) Logger::WriteMessage("CORE TRACE: "##msg##"\n"##__VA_ARGS__)
	#define KE_CORE_INFO(msg, ...) Logger::WriteMessage("CORE INFO: "##msg##"\n"##__VA_ARGS__)
	#define KE_CORE_WARN(msg, ...) Logger::WriteMessage("CORE WARN: "##msg##"\n"##__VA_ARGS__)
	#define KE_CORE_ERROR(msg, ...) Logger::WriteMessage("CORE ERROR: "##msg##"\n"##__VA_ARGS__)
	#define KE_CORE_CRITICAL(msg, ...) Logger::WriteMessage("CORE CRITICAL: "##msg##"\n"##__VA_ARGS__)

	#define KE_TRACE(msg, ...) Logger::WriteMessage("TRACE: "##msg##"\n"##__VA_ARGS__)
	#define KE_INFO(msg, ...) Logger::WriteMessage("INFO: "##msg##"\n"##__VA_ARGS__)
	//#define KE_INFO(msg) Logger::WriteMessage("INFO: "##msg##"\n")
	#define KE_WARN(msg, ...) Logger::WriteMessage("WARN: "##msg##"\n"##__VA_ARGS__)
	#define KE_ERROR(msg, ...) Logger::WriteMessage("ERROR: "##msg##"\n"##__VA_ARGS__)
	#define KE_CRITICAL(msg, ...) Logger::WriteMessage("CRITICAL: "##msg##"\n"##__VA_ARGS__)
#else
	#define KE_CORE_TRACE(...) KE::Log::s_coreLogger->trace(__VA_ARGS__)
	#define KE_CORE_INFO(...) KE::Log::s_coreLogger->info(__VA_ARGS__)
	#define KE_CORE_WARN(...) KE::Log::s_coreLogger->warn(__VA_ARGS__)
	#define KE_CORE_ERROR(...) KE::Log::s_coreLogger->error(__VA_ARGS__)
	#define KE_CORE_CRITICAL(...) KE::Log::s_coreLogger->critical(__VA_ARGS__)

	#define KE_TRACE(...) KE::Log::s_clientLogger->trace(__VA_ARGS__)
	#define KE_INFO(...) KE::Log::s_clientLogger->info(__VA_ARGS__)
	#define KE_WARN(...) KE::Log::s_clientLogger->warn(__VA_ARGS__)
	#define KE_ERROR(...) KE::Log::s_clientLogger->error(__VA_ARGS__)
	#define KE_CRITICAL(...) KE::Log::s_clientLogger->critical(__VA_ARGS__)
#endif

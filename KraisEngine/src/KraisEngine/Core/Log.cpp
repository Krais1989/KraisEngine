#include <ke_pch.h>

#include "Log.h"

void KE::Log::Init()
{
	s_coreLogger = spdlog::stdout_color_mt("KraisEngine");
	//s_coreLogger->set_level(spdlog::level::trace);

	s_clientLogger = spdlog::stdout_color_mt("Client");
	//s_clientLogger->set_level(spdlog::level::trace);
}

std::shared_ptr<spdlog::logger> KE::Log::s_clientLogger = nullptr;
std::shared_ptr<spdlog::logger> KE::Log::s_coreLogger = nullptr;

#pragma once

#include "KraisEngine/Core/Log.h"
#include "KraisEngine/Core/CApplication.h"

/*
	Входная точка сборки
	Объявляется функция создания приложения Krais::CreateApplication(), которая объявлена в CApplication.h и должна быть реализована в приложении.
	Обычно в приложении использующем движок создаётся класс наследник CApplication, который возвращается в теле реализованной CreateApplication().

	Таким образом, в клиентском приложении нужно не прописывать main, а указать реализацию Krais::CreateApplication
*/

#ifdef KE_PLATFORM_WINDOWS


extern KE::CApplication* KE::CreateApplication();

int main(int argc, char** argv) {

	//printf("Krais Entry Point\n");
	KE::Log::Init();
	KE_CORE_INFO("RUNNING");
	KE_CORE_WARN("RUNNING");
	KE_CORE_ERROR("RUNNING");
	
	KE_INFO("RUNNING");
	KE_WARN("RUNNING");
	KE_ERROR("RUNNING");
	
	auto app = KE::CreateApplication();
	app->Run();
	delete app;

	system("\n\npause");
}
#else
#error Krais Engine only support windows
#endif
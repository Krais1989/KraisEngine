#pragma once


/*
	Входная точка сборки
	Объявляется функция создания приложения Krais::CreateApplication(), которая объявлена в CApplication.h и должна быть реализована в приложении.
	Обычно в приложении использующем движок создаётся класс наследник CApplication, который возвращается в теле реализованной CreateApplication().

	Таким образом, в клиентском приложении нужно не прописывать main, а указать реализацию Krais::CreateApplication
*/

#ifdef KRAIS_PLATFORM_WINDOWS

extern Krais::CApplication* Krais::CreateApplication();

int main(int argc, char** argv) {
	printf("Krais Entry Point\n");
	auto app = Krais::CreateApplication();
	app->Run();
	delete app;
}
#else
#error Krais Engine only support windows
#endif
#pragma once

#ifdef KRAIS_PLATFORM_WINDOWS
	#ifdef KRAIS_BUILD_DLL
		#define KRAIS_API __declspec(dllexport)
	#else
		#define KRAIS_API __declspec(dllimport)
	#endif
#else
#error Krais Engine only support windows
#endif
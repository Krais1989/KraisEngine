#pragma once

#define KRAIS_API

#ifdef KE_PLATFORM_WINDOWS
	#ifdef KE_DYNAMIC
		#ifdef KE_BUILD_DLL
			#define KRAIS_API __declspec(dllexport)
		#else
			#define KRAIS_API __declspec(dllimport)
		#endif
	#endif
#else
#error Krais Engine only support windows
#endif

#pragma once

/* Базовый заголовочный файл для внутренних исходников */
/* Содержит общий системный функционал движка */

#define KE_API

#ifdef KE_PLATFORM_WINDOWS
#ifdef KE_DYNAMIC
#ifdef KE_BUILD_DLL
#define KE_API __declspec(dllexport)
#else
#define KE_API __declspec(dllimport)
#endif
#endif
#else
#error Krais Engine only support windows
#endif

#include <KraisEngine/Core/Log.h>

#define BIT(x) (1 << x)

#define EVENT_BIND(cb) std::bind(cb, this, std::placeholders::_1)
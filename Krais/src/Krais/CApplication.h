#pragma once
#include "Core.h"

namespace Krais {
	class KRAIS_API CApplication
	{
	public:
		CApplication();
		virtual ~CApplication();

		void Run();
	};

	/* Определить в приложении */
	CApplication* CreateApplication();
}



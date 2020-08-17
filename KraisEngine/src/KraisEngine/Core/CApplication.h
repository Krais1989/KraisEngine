#pragma once

#include <ke_api_defines.h>
#include <chrono>
#include <KraisEngine/Core/Log.h>

namespace KE {
	class KRAIS_API CApplication
	{
	private:
		bool m_isRun = true;
	public:
		CApplication();
		virtual ~CApplication();

		virtual void Run();
		virtual void StopApplication();

	protected:
		virtual void Update(float dt_sec);
	};

	/* Определить в приложении */
	CApplication* CreateApplication();
}



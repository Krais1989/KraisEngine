#include <ke_pch.h>

#include "CApplication.h"

namespace KE {
	CApplication::CApplication()
	{
	}

	CApplication::~CApplication()
	{
	}

	void CApplication::Update(float dt_sec)
	{

	}

	void CApplication::Run()
	{
		/*
			Используется счётчик лага (lag). При достижении определенного значения (maxLag) будет произведено обновление
			Переменная fps
		*/

		using clock = std::chrono::high_resolution_clock;

		auto lastTime = clock::now();			// переменная последнего обновления фрейма
		auto lag = std::chrono::nanoseconds(0);	// счётчик лага

		double maxFps = 60;											// максимальное количество обновлений в секунду
		double nsFreq = 1.0 / maxFps * 1000000000.0;				// частота обновления в ns
		auto maxLag = std::chrono::nanoseconds((long long)nsFreq);	// ожидаемый лаг обновления в ns

		KE_CORE_INFO("Running");
		while (m_isRun) {
			auto curTime = clock::now();	// время на текущем фрейме
			auto dft = curTime - lastTime;	// время между фреймами в ns.
			lastTime = curTime;				// фиксация времени обновления кадра
			lag += dft;						// Приращение лага
			
			if (lag > maxLag) {
				float dt = 1.0f * lag.count() / 1000000000.0f; // время обновления в секундах
				Update(dt);
				lag = std::chrono::nanoseconds(0);
			}
		}
	}

	void CApplication::StopApplication()
	{
		m_isRun = false;
	}

}


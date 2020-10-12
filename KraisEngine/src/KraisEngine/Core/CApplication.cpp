#include <ke_pch.h>

#include "CApplication.h"

namespace KE {

	CApplication::CApplication()
	{
		auto fpsToNano = [](double maxFps) {
			double nsFreq = 1.0 / maxFps * 1000000000.0;
			return std::chrono::nanoseconds((long long)nsFreq);
		};

		m_updateTimer = std::make_unique<CThrottler>(fpsToNano(3));
		m_renderTimer = std::make_unique<CThrottler>(fpsToNano(1));
	}

	CApplication::~CApplication()
	{
		if (m_graphics != nullptr)
			delete m_graphics;
	}

	int CApplication::InitGraphics(const CGraphicsManager::InitData& initData)
	{
		m_graphics = new CGraphicsManager();
		return m_graphics->Initialize(initData);
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

		KE_CORE_INFO("Running");
		while (m_isRun || !m_graphics->ShouldClose()) {
			auto curTime = clock::now();	// время на текущем фрейме
			auto dft = curTime - lastTime;	// время между фреймами в ns.
			lastTime = curTime;				// фиксация времени обновления кадра

			if (m_updateTimer->Update(dft)) {
				Update(m_updateTimer->GetTimeFloat());
			}

			if (m_renderTimer->Update(dft)) {
				Render();
			}
		}
	}

	void CApplication::Update(float dt_sec)
	{

	}

	void CApplication::Render()
	{
		m_graphics->ClearScreen();
		//m_graphics->SetViewport();

		Render_Internal();

		m_graphics->SwapBuffers();

		m_graphics->PollEvents();
	}

	void CApplication::Render_Internal()
	{

	}

	void CApplication::StopApplication()
	{
		m_isRun = false;
	}

}


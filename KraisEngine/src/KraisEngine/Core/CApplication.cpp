#include <ke_pch.h>
#include "CApplication.h"

namespace KE {

	CApplication::CApplication()
	{
		m_Window = std::unique_ptr<CWindow>(CWindow::Create());
		m_Window->SetEventCallback(std::bind(&CApplication::OnEvent, this, std::placeholders::_1));

		auto fpsToNano = [](double maxFps) {
			double nsFreq = 1.0 / maxFps * 1000000000.0;
			return std::chrono::nanoseconds((long long)nsFreq);
		};

		m_updateTimer = std::unique_ptr<CThrottler>(new CThrottler(fpsToNano(3)));
		m_renderTimer = std::unique_ptr<CThrottler>(new CThrottler(fpsToNano(1)));
	}

	CApplication::~CApplication()
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

		KE_CORE_INFO("Running");
		while (m_Running) {
			auto curTime = clock::now();	// время на текущем фрейме
			auto dft = curTime - lastTime;	// время между фреймами в ns.
			lastTime = curTime;				// фиксация времени обновления кадра

			if (m_updateTimer->Update(dft)) {
				Update(m_updateTimer->GetTimeFloat());
			}

			if (m_renderTimer->Update(dft)) {
				Render();
			}

			m_Window->OnUpdate();
		}
	}

	void CApplication::Update(float dt_sec)
	{
	}

	void CApplication::Render()
	{
	}

	void CApplication::OnEvent(CEvent& ev)
	{
		KE_CORE_INFO("{0}", ev.ToString());

		if (ev.GetEventCategory() == KE_EventCategory_Application) {
			switch (ev.GetEventType())
			{
			case EEventType::WindowResize:
				break;
			case EEventType::WindowClose:
				m_Running = false;
				break;
			}
		}

	}

	void CApplication::StopApplication()
	{
		m_Running = false;
	}

}


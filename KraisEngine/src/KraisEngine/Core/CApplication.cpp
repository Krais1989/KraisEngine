#include <ke_pch.h>
#include "CApplication.h"

#include <glad/glad.h>

namespace KE {

	CApplication* CApplication::m_Instance;

	bool CApplication::OnWindowClose(const CWindowCloseEvent& ev)
	{
		StopApplication();
		return true;
	}

	CApplication::CApplication()
	{
		m_Instance = this;

		m_Window = std::unique_ptr<CWindow>(CWindow::Create());
		m_Window->SetEventCallback(BIND_EVENT_FN(&CApplication::OnEvent));

		auto fpsToNano = [](double maxFps) {
			double nsFreq = 1.0 / maxFps * 1000000000.0;
			return std::chrono::nanoseconds((long long)nsFreq);
		};

		m_updateTimer = std::unique_ptr<CThrottler>(new CThrottler(fpsToNano(60)));
		m_renderTimer = std::unique_ptr<CThrottler>(new CThrottler(fpsToNano(60)));
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
		}
	}

	void CApplication::Update(float dt_sec)
	{
		for (CLayer* layer : m_LayerStack) {
			layer->OnUpdate(dt_sec);
		}
	}

	void CApplication::Render()
	{
		glClearColor(.6f, .6f, .1f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		for (CLayer* layer : m_LayerStack) {
			layer->OnRender();
		}

		m_Window->OnUpdate();
	}

	void CApplication::OnEvent(CEvent& ev)
	{
		//KE_CORE_INFO("{0}", ev.ToString());

		CEventDispatcher dispatcher(ev);
		dispatcher.Dispatch<CWindowCloseEvent>(BIND_EVENT_FN(&CApplication::OnWindowClose));

		for (auto it = m_LayerStack.rbegin(); it != m_LayerStack.rend(); ++it) {
			if (ev.Handled)
				break;
			(*it)->OnEvent(ev);
		}
	}

	void CApplication::PushLayer(CLayer* layer)
	{
		m_LayerStack.PushLayer(layer);
	}

	void CApplication::PushOverlay(CLayer* layer)
	{
		m_LayerStack.PushOverlay(layer);
	}

	void CApplication::StopApplication()
	{
		m_Running = false;
	}



}


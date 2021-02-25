#include <ke_pch.h>

#include "CApplication.h"

#include <glad/glad.h>

using namespace std::chrono_literals;

namespace KE {

	CApplication* CApplication::m_Instance = nullptr;

	bool CApplication::OnWindowClose(const CWindowCloseEvent& ev)
	{
		StopApplication();
		return true;
	}

	CApplication::CApplication() 
		: m_updateTimer(16ms), m_renderTimer(16ms)		
	{
		m_Instance = this;

		m_Window = std::unique_ptr<CWindow>(CWindow::Create());
		m_Window->SetEventCallback(BIND_EVENT_FN(&CApplication::OnEvent));

		m_CameraController = std::make_unique<CCameraController>();
		m_CameraController->SetCamera(std::make_shared<CCamera>());
	}

	CApplication::~CApplication()
	{
	}

	void CApplication::Run()
	{
		using clock = std::chrono::high_resolution_clock;
		auto lastTime = clock::now();			// ���������� ���������� ���������� ������
		auto lag = std::chrono::nanoseconds(0);	// ������� ����

		KE_CORE_INFO("Running");
		while (m_Running) {

			UpdateEachFrame();

			auto curTime = clock::now();	// ����� �� ������� ������
			auto dft = curTime - lastTime;	// ����� ����� �������� � ns.
			lastTime = curTime;				// �������� ������� ���������� �����

			if (m_updateTimer.Update(dft)) {
				m_Window->PoolEvents();
				Update(m_updateTimer.GetThrottle());
			}

			if (m_renderTimer.Update(dft)) {
				Render();
				m_Window->Render();
			}
		}
	}

	void CApplication::Update(float dt_sec)
	{
		//KE_CORE_INFO("Update {0}ms", dt_sec);

		m_CameraController->Update(dt_sec);

		for (auto& layer : m_LayerStack) {
			layer->OnUpdate(dt_sec);
		}

		auto& cam = m_CameraController->GetCamera();

		m_AudioManager.SetListenerPosition(cam->GetPosition(), cam->GetForward(), cam->GetUp());
	}

	void CApplication::Render()
	{
		glClearColor(.6f, .6f, .1f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		for (auto& layer : m_LayerStack) {
			layer->OnRender();
		}
	}

	void CApplication::OnEvent(CEvent& ev)
	{
		//KE_CORE_INFO("{0}", ev.ToString());

		m_AudioManager.OnEvent(ev);

		CEventDispatcher dispatcher(ev);
		dispatcher.Dispatch<CWindowCloseEvent>(BIND_EVENT_FN(&CApplication::OnWindowClose));

		for (auto it = m_LayerStack.rbegin(); it != m_LayerStack.rend(); ++it) {
			if (ev.Handled)
				break;
			(*it)->OnEvent(ev);
		}
	}

	void CApplication::UpdateEachFrame()
	{
		m_AudioManager.UpdateEachFrame();
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


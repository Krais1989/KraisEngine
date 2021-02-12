#pragma once

#include <KraisEngine/Core/Core.h>
#include <KraisEngine/Core/CThrottler.h>
#include <KraisEngine/Core/CWindow.h>

#include <KraisEngine/Events/WindowEvents.h>
#include <KraisEngine/Core/CLayerStack.h>

int main(int argc, char** argv);

namespace KE {

	class KE_API CApplication
	{
	protected:
		bool m_Running = true;

		std::unique_ptr<CThrottler> m_updateTimer;
		std::unique_ptr<CThrottler> m_renderTimer;

		std::unique_ptr<CWindow> m_Window;

		CLayerStack m_LayerStack;

		bool OnWindowClose(const CWindowCloseEvent& ev);
		virtual void Update(float dt_sec);
		virtual void Render();

	public:
		CApplication();

		virtual ~CApplication();

		/// ����� ������ ����������
		/// </summary>
		virtual void Run();
		virtual void StopApplication();
		void PushLayer(CLayer* layer);
		void PushOverlay(CLayer* layer);

		void OnEvent(CEvent& ev);


		static CApplication& Get() { return *m_Instance; }
	private:
		static CApplication* m_Instance;
		friend int ::main(int argc, char** argv);
	};

	/* ���������� � ���������� */
	CApplication* CreateApplication();
}
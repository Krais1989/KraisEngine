#pragma once

#include <KraisEngine/Core/Core.h>
#include <KraisEngine/Core/CThrottler.h>
#include <KraisEngine/Core/CWindow.h>

#include <KraisEngine/Events/WindowEvents.h>

namespace KE {
	 
	class KE_API CApplication
	{
	private:
		bool m_Running = true;

		std::unique_ptr<CThrottler> m_updateTimer;
		std::unique_ptr<CThrottler> m_renderTimer;

		std::unique_ptr<CWindow> m_Window;

		bool OnWindowClose(const CWindowCloseEvent& ev);

	public:
		CApplication();

		virtual ~CApplication();

		/// <summary>
		/// ����� ������ ����������
		/// </summary>
		virtual void Run();
		virtual void StopApplication();

	protected:
		/// <summary>
		/// ���������� ������ ����������
		/// </summary>
		/// <param name="dt_sec"></param>
		virtual void Update(float dt_sec);

		/// <summary>
		/// ������� ����� ��� ���������. �������� ������� ������, ����� ��������
		/// </summary>
		virtual void Render();

		void OnEvent(CEvent&);

	};

	/* ���������� � ���������� */
	CApplication* CreateApplication();
}



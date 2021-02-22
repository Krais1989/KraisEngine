#pragma once

#include "KraisEngine/Core/Core.h"
#include "KraisEngine/Core/CWindow.h"
#include "KraisEngine/Core/CLayerStack.h"
#include "KraisEngine/Core/CThrottler.h"
#include "KraisEngine/Core/CCameraController.h"

#include "KraisEngine/Events/WindowEvents.h"

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

		std::unique_ptr<CCameraController> m_CameraController;

	protected:

		bool OnWindowClose(const CWindowCloseEvent& ev);
		virtual void Update(float dt_sec);
		virtual void Render();

	public:
		CApplication();

		virtual ~CApplication();

		std::unique_ptr<CWindow>& GetWindow() { return m_Window; }
		std::unique_ptr<CCameraController>& GetCameraController() { return m_CameraController; }

		/// Метод работы приложения
		/// </summary>
		virtual void Run();
		virtual void StopApplication();
		virtual void PushLayer(CLayer* layer);
		virtual void PushOverlay(CLayer* layer);

		virtual void OnEvent(CEvent& ev);


		static CApplication& Get() { return *m_Instance; }

	private:
		static CApplication* m_Instance;
		friend int ::main(int argc, char** argv);
	};

	/* Определить в приложении */
	CApplication* CreateApplication();
}
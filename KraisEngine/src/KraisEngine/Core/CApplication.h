#pragma once

#include "KraisEngine/Core/Core.h"
#include "KraisEngine/Core/CWindow.h"
#include "KraisEngine/Core/CLayerStack.h"
#include "KraisEngine/Core/CThrottler.h"
#include "KraisEngine/Core/CCameraController.h"

#include "KraisEngine/Events/WindowEvents.h"
#include "KraisEngine/Core/CAudioManager.h"

#include "KraisEngine/Render/CGraphicsContext.h"

int main(int argc, char** argv);

namespace KE {

	class KE_API CApplication
	{
	protected:
		bool m_Running = true;

		CThrottler m_updateTimer;
		CThrottler m_renderTimer;

		CLayerStack m_LayerStack;
		CAudioManager m_AudioManager;

		std::unique_ptr<CGraphicsContext> m_GraphicsContext;
		std::unique_ptr<CWindow> m_Window;
		std::unique_ptr<CCameraController> m_CameraController;

		virtual void Update(float dt_sec);
		virtual void UpdateEachFrame();
		virtual void Render();

		virtual void PushLayer(CLayer* layer);
		virtual void PushOverlay(CLayer* layer);
		virtual void OnEvent(CEvent& ev);

		virtual bool OnWindowClose(const CWindowCloseEvent& ev);

		CApplication();
		virtual ~CApplication();

	public:

		CAudioManager& GetAudioManager() { return m_AudioManager; }

		std::unique_ptr<CWindow>& GetWindow() { return m_Window; }
		std::unique_ptr<CGraphicsContext>& GetGraphicsContext() { return m_GraphicsContext; }
		std::unique_ptr<CCameraController>& GetCameraController() { return m_CameraController; }

		/// Метод работы приложения
		/// </summary>
		virtual void Run();
		virtual void StopApplication();

		static CApplication& Get() { return *m_Instance; }

	private:
		static CApplication* m_Instance;
		friend int ::main(int argc, char** argv);
	};

	/* Определить в приложении */
	CApplication* CreateApplication();
}
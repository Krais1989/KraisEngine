#pragma once

#include <ke_pch.h>
#include <KraisEngine/Core/CWindow.h>
#include "KraisEngine/Render/CGraphicsContext.h"

struct GLFWwindow;

namespace KE
{
	class KE_API CWindow_WinImpl : public CWindow
	{

	public:

		CWindow_WinImpl(const SWindowProps& prop);
		virtual ~CWindow_WinImpl();

		void OnUpdate() override;
		const std::string& GetTitle() const override;
		unsigned int GetWidth() const override;
		unsigned int GetHeight() const override;
		void SetVSync(bool enable) override;
		bool IsVSyncEnabled() const override;
		void SetEventCallback(const EventCallbackFn& evCallback) override;

	private:
		void Init(const SWindowProps& prop);
		void Shutdown();

	private:
		GLFWwindow* m_Window;
		std::unique_ptr<CGraphicsContext> m_GraphicsContext;

		/// <summary>
		/// Данные для пробрасывание в GLFW колбеки
		/// </summary>
		struct SWindowData {
			std::string Title;
			unsigned int Width = 0;
			unsigned int Height = 0;
			bool VSync;

			EventCallbackFn EventCallback;
			// Указатель на функцию отравки событий 
			// EventCallbackFn EventCallback;
		};
		SWindowData m_Data;
	};
}


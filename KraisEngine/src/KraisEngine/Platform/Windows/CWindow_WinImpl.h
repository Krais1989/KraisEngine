#pragma once

#include <ke_pch.h>
#include <KraisEngine/Core/CWindow.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

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


		virtual void SetEventCallback(const EventCallbackFn& evCallback);

	private:
		void Init(const SWindowProps& prop);
		void Shutdown();

	private:
		GLFWwindow* m_Window;

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


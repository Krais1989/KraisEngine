#pragma once

#include <ke_pch.h>
#include <KraisEngine/Core/CWindow.h>
#include "KraisEngine/Render/CGraphicsContext.h"

struct GLFWwindow;

namespace KE
{
	class KE_API CWindow_WinImpl : public CWindow
	{
	private:
		GLFWwindow* m_Window;
		std::unique_ptr<CGraphicsContext> m_GraphicsContext; // TODO: окно не владеет контекстом
	protected:
		virtual void Render() override;
		virtual void PoolEvents() override;

	public:

		CWindow_WinImpl(const SWindowInitData& prop);
		virtual ~CWindow_WinImpl();

		virtual void* GetInternalWindowObject() override { return (void*)m_Window; };

		const std::string& GetTitle() const override;
		virtual void SetTitle(const char* title) override;

		unsigned int GetWidth() const override;
		unsigned int GetHeight() const override;

		void SetVSync(bool enable) override;
		bool IsVSyncEnabled() const override;
		void SetEventCallback(const EventCallbackFn& evCallback) override;


		virtual void SetCursorEnabled(bool val) override;


		virtual void GetPosition(int* xpos, int* ypos) override;


		virtual void SetPosition(int xpos, int ypos) override;


		virtual void GetSize(int* width, int* height) override;


		virtual void SetSize(int width, int height) override;


		virtual void SetMaxSize(int min_width, int min_height, int max_width, int max_height) override;


		virtual float GetOpacity() override;


		virtual void SetOpacity(float opacity) override;


		virtual void Minimize() override;


		virtual void Maximize() override;


		virtual void Restore() override;


		virtual void Show() override;


		virtual void Hide() override;


		virtual void Focus() override;


		virtual void RequestAttention() override;

	private:
		void Init(const SWindowInitData& prop);
		void Shutdown();

	private:

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


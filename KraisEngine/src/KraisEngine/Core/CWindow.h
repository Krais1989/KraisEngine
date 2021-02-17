#pragma once

#include <ke_pch.h>
#include <KraisEngine/Core/Core.h>
#include <KraisEngine/Events/CEvent.h>

namespace KE {

	struct KE_API SWindowProps {
		std::string Title;
		unsigned int Width;
		unsigned int Height;

		SWindowProps(const std::string& title = "Krais Engine",
			unsigned int width = 1280,
			unsigned int height = 720
		) :Title(title), Width(width), Height(height)
		{
		}
	};

	class KE_API CWindow
	{
	public:
		
		using EventCallbackFn = std::function<void(CEvent&)>;

		virtual void SetEventCallback(const EventCallbackFn& evCallback) = 0;

		virtual ~CWindow() = default;
		virtual void OnUpdate() = 0;

		virtual const std::string& GetTitle() const = 0;
		virtual unsigned int GetWidth() const = 0;
		virtual unsigned int GetHeight() const = 0;

		virtual void SetVSync(bool enable) = 0;
		virtual bool IsVSyncEnabled() const = 0;

		virtual void* GetWindowObject() = 0;

		/// <summary>
		/// Фабричный метод создания окна
		/// Реализуется для каждой платформы в соответствующем классе
		/// </summary>
		static CWindow* Create(const SWindowProps& data = SWindowProps());
	};
}




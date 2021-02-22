#pragma once

#include "ke_pch.h"
#include <KraisEngine/Core/Core.h>

namespace KE
{
#define KE_EVENT_TYPE(event_type) static EEventType GetStaticType() { return EEventType::event_type; }\
								virtual EEventType GetEventType() const override { return GetStaticType(); }\
								virtual const char* GetEventName() const override { return #event_type; }

#define KE_EVENT_CATEGORY_FLAGS(event_category) virtual int GetEventCategory() const override { return event_category; }


	enum class EEventType {
		None = 0,
		WindowResize, WindowClose, WindowFocus, WindowLostFocus, WindowMoved,
		KeyPressed, KeyReleased, KeyRepeated, KeyTyped,
		MouseButtonPressed, MouseButtonReleased, MouseMoved, MouseScrolled
	};

	enum EEventCategory {
		None = 0,

		KE_EventCategory_Application = BIT(0),
		KE_EventCategory_Input = BIT(1),
		KE_EventCategory_Keyboard = BIT(2),
		KE_EventCategory_Mouse = BIT(3),
		KE_EventCategory_MouseButton = BIT(4)
	};

	class KE_API CEvent
	{
	public:
		bool Handled = false;
		virtual EEventType GetEventType() const = 0;
		virtual int GetEventCategory() const = 0;
		virtual const char* GetEventName() const = 0;
		virtual std::string ToString() const { return GetEventName(); }
		bool IsInCategory(EEventCategory category) { return GetEventCategory() & category; }
	};

	class KE_API CEventDispatcher {

	private:
		template<typename T>
		using EventFn = std::function<bool(T&)>;

	public:

		CEventDispatcher(CEvent& event) : m_Event(event) {
		}

		template<typename T>
		bool Dispatch(EventFn<T> func) {
			if (m_Event.GetEventType() == T::GetStaticType()) {
				m_Event.Handled = func(*(T*)&m_Event);
				return true;
			}
			return false;
		}

	private:
		CEvent& m_Event;
	};

	inline std::ostream& operator<<(std::ostream& os, const CEvent& e)
	{
		return os << e.ToString();
	}
}

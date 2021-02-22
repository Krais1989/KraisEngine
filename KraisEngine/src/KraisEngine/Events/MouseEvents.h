#pragma once

#include "CEvent.h"
#include "KraisEngine/Core/MouseCodes.h"

namespace KE
{
	class KE_API CMouseButtonEvent : public CEvent {
	public:
		KE_EVENT_CATEGORY_FLAGS(KE_EventCategory_Input | KE_EventCategory_Mouse | KE_EventCategory_MouseButton);
		MouseCode GetMouseButton() const { return m_MouseCode; }

		virtual std::string ToString() const
		{
			std::stringstream ss;
			ss << GetEventName() << ": " << m_MouseCode;
			return ss.str();
		}

	protected:

		CMouseButtonEvent(const MouseCode code) : m_MouseCode(code) {}
		MouseCode m_MouseCode;
	};

	class KE_API CMouseButtonPressedEvent : public CMouseButtonEvent {
	public:
		KE_EVENT_TYPE(MouseButtonPressed);
		CMouseButtonPressedEvent(const MouseCode code) : CMouseButtonEvent(code) {}
	};

	class KE_API CMouseButtonReleasedEvent : public CMouseButtonEvent {
	public:
		KE_EVENT_TYPE(MouseButtonReleased);
		CMouseButtonReleasedEvent(const MouseCode code) : CMouseButtonEvent(code) {}
	};

	class KE_API CMouseScrollEvent : public CEvent {
	public:
		KE_EVENT_TYPE(MouseScrolled);
		KE_EVENT_CATEGORY_FLAGS(KE_EventCategory_Input | KE_EventCategory_Mouse);
		CMouseScrollEvent(float ox, float oy)
			:m_XOffset(ox), m_YOffset(oy)
		{ }
	protected:
		float m_XOffset, m_YOffset;
	};

	class KE_API CMouseMoveEvent : public CEvent {
	public:
		KE_EVENT_TYPE(MouseMoved);
		KE_EVENT_CATEGORY_FLAGS(KE_EventCategory_Input | KE_EventCategory_Mouse);
		CMouseMoveEvent(float mx, float my)
			:m_X(mx), m_Y(my)
		{ }

		virtual std::string ToString() const
		{
			std::stringstream ss;
			ss << GetEventName() << ": " << "(" << m_X << ":" << m_Y << ")";
			return ss.str();
		}

	public:
		float GetMX() const { return m_X; }
		float GetMY() const { return m_Y; }

	protected:
		float m_X, m_Y;
	};
}
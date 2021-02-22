#pragma once

#include "CEvent.h"
#include "KraisEngine/Core/KeyCodes.h"

namespace KE
{
	class CKeyEvent : public CEvent {
	public:
		KE_EVENT_CATEGORY_FLAGS(KE_EventCategory_Input | KE_EventCategory_Keyboard);

		virtual std::string ToString() const override
		{
			std::stringstream ss;
			ss << GetEventName() << ": " << m_Key;
			return ss.str();
		}

		KeyCode GetKey() const { return m_Key; }

		virtual ~CKeyEvent()
		{
			//KE_INFO("Destruct");
		}

	protected:
		CKeyEvent(KeyCode key) : m_Key(key) {}
		KeyCode m_Key;
	};

	class KE_API CKeyPressedEvent : public CKeyEvent {
	public:
		CKeyPressedEvent(KeyCode key) : CKeyEvent(key) { }
		KE_EVENT_TYPE(KeyPressed);
	};

	class KE_API CKeyReleasedEvent : public CKeyEvent {
	public:
		CKeyReleasedEvent(KeyCode key) : CKeyEvent(key) { }
		KE_EVENT_TYPE(KeyReleased);
	};

	class KE_API CKeyRepeatedEvent : public CKeyEvent {
	public:
		CKeyRepeatedEvent(KeyCode key) : CKeyEvent(key) { }
		KE_EVENT_TYPE(KeyRepeated);
	};

	class KE_API CKeyTypedEvent : public CKeyEvent {
	public:
		CKeyTypedEvent(KeyCode key) : CKeyEvent(key) {}
		KE_EVENT_TYPE(KeyTyped);
	};
}
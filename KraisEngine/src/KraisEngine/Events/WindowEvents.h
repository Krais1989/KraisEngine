#pragma once

#include "CEvent.h"

namespace KE
{
	class KE_API CWindowCloseEvent : public CEvent {
	public:
		KE_EVENT_TYPE(WindowClose);
		KE_EVENT_CATEGORY_FLAGS(KE_EventCategory_Application);
	};
	
	class KE_API CWindowResizeEvent : public CEvent {
	public:
		KE_EVENT_TYPE(WindowResize);
		KE_EVENT_CATEGORY_FLAGS(KE_EventCategory_Application);
	
		int Width;
		int Height;
	
		CWindowResizeEvent(int width, int height)
			: Width(width), Height(height) {
		}
	
		virtual std::string ToString() const {
			std::stringstream ss;
			ss << GetEventName() << "(" << Width << ":" << Height << ")";
			return ss.str();
		}
	};
}
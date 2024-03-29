#pragma once

#include <KraisEngine/Core/Core.h>
#include <KraisEngine/Events/CEvent.h>

namespace KE
{
	class CLayer
	{
	public:
	
		virtual void OnRender();
		virtual void OnAttach();
		virtual void OnDetach();
		virtual void OnUpdate(float dt);
		virtual void OnEvent(CEvent& ev);

		std::string GetDebugName() const { return m_DebugName; }
	protected:
		std::string m_DebugName;
	};
}

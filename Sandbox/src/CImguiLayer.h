#pragma once

#include <KraisEngine/Core/CLayer.h>

namespace KE
{
	class CImguiLayer : public CLayer
	{
	public:
		virtual void OnAttach();
	
	
		virtual void OnDetach();
	
	
		virtual void OnUpdate(float dt);
	
	
		virtual void OnEvent(CEvent& ev);
	
	};
	
}

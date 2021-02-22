#include "ke_pch.h"
#include "CLayer.h"

namespace KE
{
	
	void CLayer::OnRender()
	{

	}

	void CLayer::OnAttach()
	{
		KE_CORE_INFO("Layer OnAttach: {0}", GetDebugName());
	}
	
	void CLayer::OnDetach()
	{
		KE_CORE_INFO("Layer OnDetach: {0}", GetDebugName());
	}
	
	void CLayer::OnUpdate(float dt)
{
		KE_CORE_INFO("Layer OnUpdate: {0} : {1}", GetDebugName(), dt);
	}
	
	void CLayer::OnEvent(CEvent& ev)
	{
		KE_CORE_INFO("Layer OnEvent: {0} > {1}", GetDebugName(), ev.ToString());
	}
}

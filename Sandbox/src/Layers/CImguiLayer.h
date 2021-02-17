#pragma once

#include <ke_pch.h>
#include <KraisEngine.h>

class CImguiLayer : public KE::CLayer
{
public:
	CImguiLayer();

	virtual void OnAttach();


	virtual void OnDetach();


	virtual void OnUpdate(float dt);


	virtual void OnEvent(KE::CEvent& ev);



	virtual void OnRender();

protected:
	bool m_ShowDemo = true;
	bool m_CameraTool = true;

};

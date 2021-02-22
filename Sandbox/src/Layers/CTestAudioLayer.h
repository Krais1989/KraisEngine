#pragma once

#include <ke_pch.h>
#include <KraisEngine.h>

class CTestAudioLayer : public KE::CLayer
{
public:
	virtual void OnRender();


	virtual void OnAttach();


	virtual void OnDetach();


	virtual void OnUpdate(float dt);


	virtual void OnEvent(KE::CEvent& ev);

};


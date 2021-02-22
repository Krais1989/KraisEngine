#pragma once

#include <ke_pch.h>
#include <KraisEngine.h>

#include <fmod.hpp>
#include <fmod_errors.h>

class CTestAudioLayer : public KE::CLayer
{
public:

	CTestAudioLayer();

	~CTestAudioLayer()
	{

		m_FMODSystem->release();
	}

	virtual void OnRender();


	virtual void OnAttach();


	virtual void OnDetach();


	virtual void OnUpdate(float dt);


	virtual void OnEvent(KE::CEvent& ev);



protected:

	void LoadMusic(const char* path);
	void PlayMusic(FMOD::Sound* music);
	void PlayMusic(int index);
	void PlayNextMusic();

	FMOD::System* m_FMODSystem = nullptr;
	FMOD::ChannelGroup* m_ChannelGroup = nullptr;
	FMOD::Channel* m_Channel = nullptr;

	std::vector<FMOD::Sound*> m_Sounds;


	float m_Time = 0;
	float m_PosHorizontal = 0;
	float m_PosVertical = 0;

	int m_CurMusicIndex = 0;

	float m_MinDist = 0.0f;
	float m_MaxDist = 2000.0f;
	float m_ChannelVolume = 0.5f;
};


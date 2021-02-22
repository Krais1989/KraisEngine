#pragma once

#include <fmod.hpp>
#include <fmod_errors.h>

#include "KraisEngine/Core/Core.h"
#include "KraisEngine/Events/CEvent.h"
#include "KraisEngine/Events/KeyEvents.h"

namespace KE {
	class CAudioManager
	{
	public:
		CAudioManager();
		~CAudioManager();


		void LoadMusic(const char* path);

		void PlayMusic(FMOD::Sound* music);

		void PlayMusic(int index);

		void PlayNextMusic();

		void OnEvent(CEvent& ev);

		void UpdateEachFrame();

		void SetListenerPosition(const glm::vec3& pos, const glm::vec3& forward, const glm::vec3& up);

	protected:
		FMOD::System* m_System = nullptr;
		FMOD::ChannelGroup* m_ChannelGroup = nullptr;
		FMOD::Channel* m_Channel = nullptr;
		std::vector<FMOD::Sound*> m_Sounds;

		int m_CurMusicIndex = 0;

		float m_MinDist = 0.0f;
		float m_MaxDist = 2000.0f;
		float m_ChannelVolume = 0.5f;
	};
}



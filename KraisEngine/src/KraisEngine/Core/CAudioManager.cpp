#include "ke_pch.h"

#include "CAudioManager.h"

namespace KE {

	FMOD_RESULT F_CALLBACK channelGroupCallback(FMOD_CHANNELCONTROL* channelControl,
		FMOD_CHANNELCONTROL_TYPE controlType, FMOD_CHANNELCONTROL_CALLBACK_TYPE callbackType,
		void* commandData1, void* commandData2)
	{
		std::cout << "Callback called for " << controlType << std::endl;
		return FMOD_OK;
	}

	CAudioManager::CAudioManager()
	{
		FMOD_RESULT result;
		m_System = NULL;
		result = FMOD::System_Create(&m_System);

		if (result != FMOD_OK) {
			KE_ERROR("FMOD CREATE ERROR! {0} {1}", result, FMOD_ErrorString(result));
			exit(-1);
		}

		//FMOD_ADVANCEDSETTINGS advSettings;
		//fmod_system->setAdvancedSettings(&advSettings);

		result = m_System->init(512, FMOD_INIT_NORMAL | FMOD_INIT_3D_RIGHTHANDED, 0);
		if (result != FMOD_OK) {
			KE_ERROR("FMOD INIT ERROR! {0} {1}", result, FMOD_ErrorString(result));
			exit(-1);
		}
	}

	CAudioManager::~CAudioManager()
	{
		if (m_System != nullptr)
			m_System->close();
	}

	void CAudioManager::LoadMusic(const char* path)
	{
		FMOD::Sound* sound;

		FMOD_RESULT result = m_System->createStream(path, FMOD_3D, nullptr, &sound);
		//FMOD_RESULT result = m_FMODSystem->createSound(path, FMOD_3D | FMOD_CREATESTREAM, 0, &sound);
		if (result != FMOD_OK) {
			KE_ERROR("FMOD LoadMusic ERROR! {0} {1}", result, FMOD_ErrorString(result));
			exit(-1);
		}

		m_Sounds.push_back(sound);
	}

	void CAudioManager::PlayMusic(int index)
	{
		//if (m_CurMusicIndex == index) return;
		m_CurMusicIndex = index % m_Sounds.size();
		KE_INFO("AudioManager play music [{0}]", m_CurMusicIndex);
		PlayMusic(m_Sounds[m_CurMusicIndex]);
	}

	void CAudioManager::PlayMusic(FMOD::Sound* music)
	{
		if (m_Channel != nullptr) {
			m_Channel->stop();
		}

		//music->set3DMinMaxDistance(); // float min max
		music->setMode(FMOD_LOOP_NORMAL); // FMOD_LOOP_OFF
		FMOD_RESULT result = m_System->playSound(music, nullptr, false, &m_Channel);
		if (result != FMOD_OK) {
			KE_ERROR(FMOD_ErrorString(result));
		}

		m_Channel->setVolume(m_ChannelVolume);
	}

	void CAudioManager::PlayNextMusic()
	{
		PlayMusic(m_CurMusicIndex + 1);
	}

	void CAudioManager::OnEvent(CEvent& ev)
	{
		if (ev.GetEventType() == EEventType::KeyPressed) {
			auto& keyEv = reinterpret_cast<CKeyEvent&>(ev);
			switch (keyEv.GetKey())
			{
			case Key::I:
				PlayNextMusic();
				break;
			case Key::O:
				m_ChannelVolume -= 0.1;
				break;
			case Key::P:
				m_ChannelVolume += 0.1;
				break;
			default:
				break;
			}
		}
	}

	void CAudioManager::UpdateEachFrame()
	{
		if (m_Channel != nullptr) {
			m_Channel->setVolume(m_ChannelVolume);
		}

		m_System->update();
	}

	void CAudioManager::SetListenerPosition(const glm::vec3& pos, const glm::vec3& forward, const glm::vec3& up)
	{
		FMOD_VECTOR listener_pos = (FMOD_VECTOR&)pos;
		//FMOD_VECTOR listener_vel;
		FMOD_VECTOR listener_forward = (FMOD_VECTOR&)forward;
		FMOD_VECTOR listener_up = (FMOD_VECTOR&)up;

		m_System->set3DListenerAttributes(0, &listener_pos, nullptr, &listener_forward, &listener_up);
	}

}

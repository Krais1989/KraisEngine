#include "CTestAudioLayer.h"
#include <glm/glm.hpp>

CTestAudioLayer::CTestAudioLayer()
{
	FMOD_RESULT result;
	m_FMODSystem = NULL;
	result = FMOD::System_Create(&m_FMODSystem);

	if (result != FMOD_OK) {
		KE_ERROR("FMOD CREATE ERROR! {0} {1}", result, FMOD_ErrorString(result));
		exit(-1);
	}

	//FMOD_ADVANCEDSETTINGS advSettings;
	//fmod_system->setAdvancedSettings(&advSettings);

	result = m_FMODSystem->init(512, FMOD_INIT_NORMAL | FMOD_INIT_3D_RIGHTHANDED, 0);
	if (result != FMOD_OK) {
		KE_ERROR("FMOD INIT ERROR! {0} {1}", result, FMOD_ErrorString(result));
		exit(-1);
	}
}

void CTestAudioLayer::OnAttach()
{
	LoadMusic("Assets/Music/loop1.mp3");
	LoadMusic("Assets/Music/Distortion melody.mp3");
	PlayMusic(0);
}


void CTestAudioLayer::OnRender()
{
}

void CTestAudioLayer::OnDetach()
{
}

void CTestAudioLayer::OnUpdate(float dt)
{
	auto& cam = KE::CApplication::Get().GetCameraController()->GetCamera();

	m_Time += dt;

	m_PosHorizontal = glm::sin(dt);


	auto& camPosition = cam->GetPosition();
	auto& camForward = cam->GetForward();
	auto& camUp = cam->GetUp();

	FMOD_VECTOR listener_pos = (FMOD_VECTOR&)camPosition;
	FMOD_VECTOR listener_vel;
	FMOD_VECTOR listener_forward = (FMOD_VECTOR&)camForward;
	FMOD_VECTOR listener_up = (FMOD_VECTOR&)camUp;

	m_FMODSystem->set3DListenerAttributes(0, &listener_pos, &listener_vel, &listener_forward, &listener_up);

	if (m_Channel != nullptr) {
		m_Channel->setVolume(m_ChannelVolume);
	}

	//m_FMODSystem->update();
}

void CTestAudioLayer::OnEvent(KE::CEvent& ev)
{
	if (ev.GetEventType() == KE::EEventType::KeyPressed) {
		auto& keyEv = reinterpret_cast<KE::CKeyEvent&>(ev);
		switch (keyEv.GetKey())
		{
		case KE::Key::I:
			PlayNextMusic();
			break;
		case KE::Key::O:
			m_ChannelVolume -= 0.1;
			break;
		case KE::Key::P:
			m_ChannelVolume += 0.1;
			break;
		default:
			break;
		}
	}
}

void CTestAudioLayer::LoadMusic(const char* path)
{
	FMOD::Sound* sound;

	FMOD_RESULT result = m_FMODSystem->createStream(path, FMOD_3D, nullptr, &sound);
	//FMOD_RESULT result = m_FMODSystem->createSound(path, FMOD_3D | FMOD_CREATESTREAM, 0, &sound);
	if (result != FMOD_OK) {
		KE_ERROR("FMOD LoadMusic ERROR! {0} {1}", result, FMOD_ErrorString(result));
		exit(-1);
	}

	m_Sounds.push_back(sound);
}

void CTestAudioLayer::PlayMusic(FMOD::Sound* music)
{
	if (m_Channel != nullptr) {
		m_Channel->stop();
	}

	//music->set3DMinMaxDistance(); // float min max
	music->setMode(FMOD_LOOP_NORMAL); // FMOD_LOOP_OFF
	FMOD_RESULT result = m_FMODSystem->playSound(music, nullptr, false, &m_Channel);
	if (result != FMOD_OK) {
		KE_ERROR(FMOD_ErrorString(result));
	}

	m_Channel->setVolume(m_ChannelVolume);
}

void CTestAudioLayer::PlayMusic(int index)
{
	//if (m_CurMusicIndex == index) return;

	m_CurMusicIndex = index % m_Sounds.size();
	PlayMusic(m_Sounds[m_CurMusicIndex]);
}

void CTestAudioLayer::PlayNextMusic()
{
	PlayMusic(m_CurMusicIndex + 1);
}


FMOD_RESULT F_CALLBACK channelGroupCallback(FMOD_CHANNELCONTROL* channelControl,
	FMOD_CHANNELCONTROL_TYPE controlType, FMOD_CHANNELCONTROL_CALLBACK_TYPE callbackType,
	void* commandData1, void* commandData2)
{
	std::cout << "Callback called for " << controlType << std::endl;
	return FMOD_OK;
}
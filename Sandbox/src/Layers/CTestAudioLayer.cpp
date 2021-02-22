#include "CTestAudioLayer.h"

#include <fmod.hpp>
#include <fmod_errors.h>
 
void CTestAudioLayer::OnAttach()
{
	FMOD_RESULT result;
	FMOD::System* fmodSystem = NULL;
	result = FMOD::System_Create(&fmodSystem);

	if (result != FMOD_OK) {
		KE_INFO("FMOD CREATE ERROR! {0} {1}", result, FMOD_ErrorString(result));
		exit(-1);
	}

	result = fmodSystem->init(512, FMOD_INIT_NORMAL, 0);
	if (result != FMOD_OK) {
		KE_INFO("FMOD INIT ERROR! {0} {1}", result, FMOD_ErrorString(result));
		exit(-1);
	}

}

void CTestAudioLayer::OnRender()
{
}

void CTestAudioLayer::OnDetach()
{
}

void CTestAudioLayer::OnUpdate(float dt)
{
}

void CTestAudioLayer::OnEvent(KE::CEvent& ev)
{
}

#include <KraisEngine.h>
#include <KraisEngine/EntryPoint.h>

#include "Layers/CTestOpenGLLayer.h"
#include "Layers/CImguiLayer.h"

class CSandbox : public KE::CApplication
{
public:
	CSandbox() : KE::CApplication() {
		PushLayer(new CTestOpenGLLayer());
		//PushOverlay(new CImguiLayer())

		GetAudioManager().LoadMusic("Assets/Music/loop1.mp3");
		GetAudioManager().LoadMusic("Assets/Music/Distortion melody.mp3");
		GetAudioManager().PlayMusic(0);
	}

	~CSandbox() override {

	}

	virtual void OnEvent(KE::CEvent& ev)
	{
		if (ev.GetEventType() == KE::EEventType::KeyPressed) {
			auto& keyEv = reinterpret_cast<KE::CKeyPressedEvent&>(ev);
			if (keyEv.GetKey() == KE::Key::ESCAPE)
				StopApplication();
		}

		KE::CApplication::OnEvent(ev);		
	}


protected:

	virtual void Update(float dt_sec) override
	{
		KE::CApplication::Update(dt_sec);
	}


	virtual void UpdateEachFrame() override
	{
		KE::CApplication::UpdateEachFrame();
	}

};

KE::CApplication* KE::CreateApplication() {
	return new CSandbox();
}
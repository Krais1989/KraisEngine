#include <KraisEngine.h>
#include <KraisEngine/EntryPoint.h>

#include "Layers/CTestOpenGLLayer.h"
#include "Layers/CImguiLayer.h"
#include "Layers/CTestAudioLayer.h"

class CSandbox : public KE::CApplication
{
public:
	CSandbox() {
		PushLayer(new CTestOpenGLLayer());
		PushLayer(new CTestAudioLayer());
		//PushOverlay(new CImguiLayer())
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

};

KE::CApplication* KE::CreateApplication() {
	return new CSandbox();
}
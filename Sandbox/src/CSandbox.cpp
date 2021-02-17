#include <KraisEngine.h>
#include <KraisEngine/EntryPoint.h>

#include "Layers/CTestOpenGLLayer.h"
#include "Layers/CImguiLayer.h"

class CSandbox : public KE::CApplication
{
public:
	CSandbox() {
		PushLayer(new CTestOpenGLLayer());
		PushOverlay(new CImguiLayer())
		//PushLayer(new TestLayer());
		/*PushOverlay(new TestOverlay());
		PushLayer(new TestLayer2())*/;
	}
	~CSandbox() override {

	}
};

KE::CApplication* KE::CreateApplication() {
	return new CSandbox();
}
#include "CSandbox.h"

CSandbox::CSandbox() : KE::CApplication()
{
	PushOverlay(new TestOverlay());
	PushLayer(new TestLayer());
	PushLayer(new TestLayer2());
}

CSandbox::~CSandbox()
{

}
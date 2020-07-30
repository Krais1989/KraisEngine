#include <Krais.h>

class Sandbox : public Krais::CApplication
{
public:
	Sandbox() {}
	~Sandbox() {}

private:

};

Krais::CApplication* Krais::CreateApplication() {
	return new Krais::CApplication();
}

//int main() {
//
//	Sandbox* sandbox = new Sandbox();
//	sandbox->Run();
//	delete sandbox;
//	return 0;
//}
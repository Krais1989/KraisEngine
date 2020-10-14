
#include <KraisEngine.h>


class CSandbox : public KE::CApplication
{
public:
	CSandbox();
	~CSandbox() override;
};

KE::CApplication* KE::CreateApplication() {
	return new CSandbox();
}

#include <KraisEngine.h>

class CSandbox : public KE::CApplication
{
public:
	CSandbox();
	~CSandbox() override;
protected:
	virtual void Update(float dt_sec) override;
};

KE::CApplication* KE::CreateApplication() {
	return new CSandbox();
}
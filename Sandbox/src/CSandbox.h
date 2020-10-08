
#include <KraisEngine.h>

#include <KraisEngine/Core/CGraphics.h>


class CSandbox : public KE::CApplication
{
public:
	CSandbox();
	~CSandbox() override;
protected:
	virtual void Update(float dt_sec) override;


	virtual void Render_Internal();

};

KE::CApplication* KE::CreateApplication() {
	return new CSandbox();
}
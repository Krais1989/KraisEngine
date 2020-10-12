#include "CSandbox.h"

CSandbox::CSandbox() : KE::CApplication()
{
	KE::CGraphicsManager::InitData graphicsData;
	graphicsData.Width = 800;
	graphicsData.Height= 800;
	graphicsData.Title = "KE Sandbox";


	InitGraphics(graphicsData);

	GetGraphics()->ClearColor(1, 0, 0, 1);
}

CSandbox::~CSandbox()
{

}

void CSandbox::Update(float dt_sec)
{
	KE_INFO("Update: {} sec", dt_sec);

}

void CSandbox::Render_Internal()
{
	KE_INFO("Render");
}

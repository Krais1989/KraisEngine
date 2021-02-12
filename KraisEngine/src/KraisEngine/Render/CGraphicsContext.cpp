#include "ke_pch.h"
#include "CGraphicsContext.h"
#include "Platform/OpenGL/COpenGLContext.h"


std::unique_ptr<KE::CGraphicsContext> KE::CGraphicsContext::Create(void* window)
{
	return std::make_unique<COpenGLContext>(static_cast<GLFWwindow*>(window));
}

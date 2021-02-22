#include "ke_pch.h"
#include "CTexture2D.h"

#include <Platform/OpenGL/COpenGLTexture2D.h>

namespace KE {
	std::shared_ptr<CTexture2D> CTexture2D::Create(const std::string& path)
	{
		return std::make_shared<COpenGLTexture2D>(path);
	}

}


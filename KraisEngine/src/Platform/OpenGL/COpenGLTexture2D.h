#pragma once

#include <ke_pch.h>
#include <KraisEngine.h>

namespace KE {
	class COpenGLTexture2D : public CTexture2D
	{
	public:
		COpenGLTexture2D(const std::string& path);
		virtual void Init(const std::string& path);
		virtual void Bind(int unit = 0);
	};
}
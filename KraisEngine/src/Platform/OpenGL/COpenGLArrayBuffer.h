#pragma once

#include "ke_pch.h"

#include "KraisEngine/Render/Buffers.h"
#include "KraisEngine/Core/Core.h"

namespace KE {
	class COpenGLArrayBuffer : public CArrayBuffer
	{
	public:
		virtual void Init(std::vector<IBindableBuffer>& buffers);


		virtual void Bind();


		virtual void Dispose();

	protected:
		bool m_Initialized = 0;

	};
}



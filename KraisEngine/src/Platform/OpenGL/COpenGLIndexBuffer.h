#pragma once

#include "ke_pch.h"
#include "KraisEngine/Core/Core.h"

#include "KraisEngine/Render/Buffers.h"

namespace KE {
	class COpenGLIndexBuffer : public CBuffer<unsigned int>
	{
	public:


		virtual void Init(std::vector<unsigned int> data);


		virtual void Dispose();


		virtual void Bind();

	protected:
		bool m_Initialized = false;

	};
}



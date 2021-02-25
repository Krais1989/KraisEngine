#pragma once

#include "KraisEngine/Render/Buffers.h"

namespace KE {
	class COpenGLVertexBuffer_PosTex : public CBuffer<SVertexAttributes_PosTex>
	{
	public:

		virtual void Init(std::vector<KE::SVertexAttributes_PosTex> data);
		virtual void Bind();
		virtual void Dispose();
	protected:
		bool m_Initialized = false;

	};

}


#pragma once

#include "ke_pch.h"
#include "KraisEngine/Core/Core.h"
#include "IBindableBuffer.h"
#include "CVertexBuffer.h"
#include "CIndexBuffer.h"

namespace KE
{
	class CArrayBuffer : public IBindableBuffer {
	protected:

		using vert_t = CVertexBuffer;
		using index_t = CIndexBuffer;
		using vert_sp = std::shared_ptr<vert_t>;
		using index_sp = std::shared_ptr<index_t>;

		vert_sp m_VertexBuffer;
		index_sp m_IndexBuffer;
	public:
		CArrayBuffer(vert_sp vert_buffer, index_sp index_buffer)
			: m_VertexBuffer(vert_buffer), m_IndexBuffer(index_buffer)
		{

		}
	};
}
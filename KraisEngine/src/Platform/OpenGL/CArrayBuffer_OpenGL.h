#pragma once

#include "KraisEngine/Render/Buffers/CArrayBuffer.h"
#include "Buffers_OpenGL.h"


namespace KE
{
	class CArrayBuffer_OpenGL : public CArrayBuffer {
	
	public:

		CArrayBuffer_OpenGL(const vert_sp& vert_buffer, const index_sp& index_buffer)
			: CArrayBuffer(vert_buffer, index_buffer)
		{
		}

		~CArrayBuffer_OpenGL()
		{
			if (m_IsInitialized)
				glDeleteVertexArrays(1, &m_ID);
			m_IsInitialized = false;
		}

		virtual void Init()
		{
			KE_CORE_ASSERT(!m_IsInitialized, "Index buffer already initialized!");
			if (m_IsInitialized) return;

			glGenVertexArrays(1, &m_ID);
			glBindVertexArray(m_ID);

			m_VertexBuffer->Bind();
			m_IndexBuffer->Bind();

			auto layout = m_VertexBuffer->GetLayout();

			for (size_t i = 0; i < layout.GetAttributesCount(); i++)
			{
				auto& attr = layout[i];
				auto attr_size = attr.GetAttributeSize();
				auto elem_count = attr.GetElementsCount();
				auto attr_type_gl = GetElementOpenGLType(attr.GetType());
				auto attr_offset = attr.GetOffset();

				glVertexAttribPointer(i, elem_count, attr_type_gl, GL_FALSE, layout.GetStride(), (void*)attr_offset);
				glEnableVertexAttribArray(i);
			}

			glBindVertexArray(0);

			m_IsInitialized = true;
		}

		virtual void Bind()
		{
			KE_CORE_ASSERT(m_IsInitialized, "VAO bind errror! Not Initialized!");
			glBindVertexArray(m_ID);
		}


	};
}
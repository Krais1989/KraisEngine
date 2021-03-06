#pragma once

#include "KraisEngine/Render/Buffers/CArrayBuffer.h"
#include "Buffers_OpenGL.h"


namespace KE
{
	class CArrayBuffer_OpenGL : public CArrayBuffer {
	
	public:

		~CArrayBuffer_OpenGL()
		{
			if (m_IsInitialized)
				glDeleteVertexArrays(1, &m_ID);
			m_IsInitialized = false;
		}

		virtual void Init()
		{
			KE_ASSERT(!m_IsInitialized, "Index buffer already initialized!");
			if (m_IsInitialized) return;

			glGenVertexArrays(1, &m_ID);
			glBindVertexArray(m_ID);

			m_VertexBuffer->Bind();
			m_IndexBuffer->Bind();

			glBindVertexArray(0);

			m_IsInitialized = true;
		}

		virtual void Bind()
		{
			KE_ASSERT(m_IsInitialized, "VAO bind errror! Not Initialized!");
			glBindVertexArray(m_ID);
		}


	};
}
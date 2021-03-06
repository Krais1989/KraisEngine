#pragma once


#include "KraisEngine/Render/Buffers/CIndexBuffer.h"
#include "Buffers_OpenGL.h"

namespace KE {

	class CIndexBuffer_OpenGL : public CIndexBuffer {

	public:

		CIndexBuffer_OpenGL(std::initializer_list<data_t> data)
			: CIndexBuffer(data)
		{
		}

		CIndexBuffer_OpenGL(const std::vector<data_t>& data)
			: CIndexBuffer(data)
		{
		}

		CIndexBuffer_OpenGL(std::vector<data_t>&& data)
			: CIndexBuffer(std::move(data))
		{
		}



		~CIndexBuffer_OpenGL()
		{
			if (m_IsInitialized)
				glDeleteBuffers(1, &m_ID);
			m_IsInitialized = false;
		}

		virtual void Init()
		{
			//KE_CORE_ASSERT(!m_IsInitialized, "Index buffer already initialized!");

			if (m_IsInitialized) return;

			glGenBuffers(1, &m_ID);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ID);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, GetSizeInBytes(), GetRawPointer(), GL_STATIC_DRAW);

			m_IsInitialized = true;
		}

		virtual void Bind()
		{
			//KE_CORE_ASSERT(m_IsInitialized, "Buffer not initialized! Try init first!");
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ID);
		}

	};

}
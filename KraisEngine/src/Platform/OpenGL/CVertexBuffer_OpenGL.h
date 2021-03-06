#pragma once

#include "KraisEngine/Render/Buffers/CVertexBuffer.h"
#include "Buffers_OpenGL.h"

namespace KE
{
	class CVertexBuffer_OpenGL : public CVertexBuffer {

	public:

		CVertexBuffer_OpenGL(CBufferLayout layout, const data_t* raw, size_t raw_size)
			: CVertexBuffer(layout, raw, raw_size)
		{
		}

		CVertexBuffer_OpenGL(CBufferLayout layout, std::initializer_list<data_t> data)
			: CVertexBuffer(layout, data)
		{
		}

		CVertexBuffer_OpenGL(CBufferLayout layout, const storage_t& data)
			: CVertexBuffer(layout, data)
		{
		}

		CVertexBuffer_OpenGL(CBufferLayout layout, storage_t&& data)
			: CVertexBuffer(layout, std::move(data))
		{
		}

		~CVertexBuffer_OpenGL()
		{
			if (m_IsInitialized)
				glDeleteBuffers(1, &m_ID);
			m_IsInitialized = false;
		}

		virtual void Init()
		{
			//KE_CORE_ASSERT(!m_IsInitialized, "Vertex  buffer already initialized!");
			if (m_IsInitialized) return;

			//m_Data.resize(data.size());
			//m_Data.insert(m_Data.end(), data.begin(), data.end());

			glGenBuffers(1, &m_ID);
			glBindBuffer(GL_ARRAY_BUFFER, m_ID);
			glBufferData(GL_ARRAY_BUFFER, m_Data.size(), &m_Data.front(), GL_STATIC_DRAW);

			size_t prevSize = 0;
			for (size_t i = 0; i < m_Layout.GetAttributesCount(); i++)
			{
				auto& attr = m_Layout[i];
				auto attr_size = attr.GetAttributeSize();
				auto elem_count = attr.GetElementsCount();

				glVertexAttribPointer(i, elem_count, GetElementOpenGLType(attr.GetType()), GL_FALSE, attr_size, (void*)prevSize);
				glEnableVertexAttribArray(i);

				prevSize += attr_size;
			}

			m_IsInitialized = true;
		}

		virtual void Bind()
		{
			//KE_CORE_ASSERT(m_IsInitialized, "VBO bind error: not initialized!");
			glBindBuffer(GL_ARRAY_BUFFER, m_ID);
		}
	};
}
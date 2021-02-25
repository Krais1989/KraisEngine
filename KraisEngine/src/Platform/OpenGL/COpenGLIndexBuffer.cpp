#include "COpenGLIndexBuffer.h"

#include <glad/glad.h>

namespace KE {

	void COpenGLIndexBuffer::Init(std::vector<unsigned int> data)
	{
		KE_ASSERT(!m_Initialized, "Index buffer already initialized!");

		if (m_Initialized) return;

		glGenBuffers(1, &m_ID);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ID);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * data.size(), data.data(), GL_STATIC_DRAW);

		m_Initialized = true;
	}

	void COpenGLIndexBuffer::Dispose()
	{
		if (m_Initialized)
			glDeleteBuffers(1, &m_ID);
		m_Initialized = false;
	}

	void COpenGLIndexBuffer::Bind()
	{
		KE_ASSERT(!m_Initialized, "Buffer not initialized! Try init first!");
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ID);
	}

}
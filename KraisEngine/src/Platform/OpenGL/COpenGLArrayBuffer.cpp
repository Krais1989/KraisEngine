#include "COpenGLArrayBuffer.h"

#include <glad/glad.h>

void KE::COpenGLArrayBuffer::Init(std::vector<IBindableBuffer>& buffers)
{
	KE_ASSERT(!m_Initialized, "Index buffer already initialized!");
	if (m_Initialized) return;

	glGenVertexArrays(1, &m_ID);
	glBindVertexArray(m_ID);

	for (auto& buf : buffers) {
		buf.Bind();
	}

	m_Initialized = true;
}

void KE::COpenGLArrayBuffer::Bind()
{
	KE_ASSERT(m_Initialized, "VAO bind errror! Not Initialized!");
	glBindVertexArray(m_ID);
}

void KE::COpenGLArrayBuffer::Dispose()
{
	if (m_Initialized)
		glDeleteVertexArrays(1, &m_ID);
	m_Initialized = false;
}

#include "COpenGLVertexBuffer.h"

#include "glad/glad.h"
#include "KraisEngine/Core/Core.h"

namespace KE {

	void COpenGLVertexBuffer_PosTex::Init(std::vector<KE::SVertexAttributes_PosTex> data)
	{
		KE_ASSERT(!m_Initialized, "Vertex  buffer already initialized!");
		if (m_Initialized) return;

		//m_Data.resize(data.size());
		//m_Data.insert(m_Data.end(), data.begin(), data.end());

		glGenBuffers(1, &m_ID);
		glBindBuffer(GL_ARRAY_BUFFER, m_ID);
		glBufferData(GL_ARRAY_BUFFER, sizeof(SVertexAttributes_PosTex) * data.size(), data.data(), GL_STATIC_DRAW);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));

		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);

		m_Initialized = true;
	}

	void COpenGLVertexBuffer_PosTex::Bind()
	{
		KE_ASSERT(!m_Initialized, "Buffer not initialized! Try init first!");
		glBindBuffer(GL_ARRAY_BUFFER, m_ID);
	}

	void COpenGLVertexBuffer_PosTex::Dispose()
	{
		if (m_Initialized)
			glDeleteBuffers(1, &m_ID);
		m_Initialized = false;
	}

}
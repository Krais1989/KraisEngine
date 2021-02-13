#include "COpenGLTexture2D.h"

#include <glad/glad.h>
#include <stb_image.h>

namespace KE {

	COpenGLTexture2D::COpenGLTexture2D(const std::string& path)
	{
		Init(path);
	}

	void COpenGLTexture2D::Init(const std::string& path)
	{
		unsigned char* data = stbi_load(path.c_str(), &m_Width, &m_Height, &m_Channels, 0);

		if (!data)
		{
			KE_CORE_ERROR("Texture load error: {0}", path);
			m_ErrorMessage = "data is null";
			return;
		}


		glGenTextures(1, &m_TextureId);
		glBindTexture(GL_TEXTURE_2D, m_TextureId);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		GLenum mode = m_Channels == 3 ? GL_RGB : GL_RGBA;

		glTexImage2D(GL_TEXTURE_2D, 0, mode, m_Width, m_Height, 0, mode, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);

		delete data;
	}

	void COpenGLTexture2D::Bind(int unit /*= 0*/)
	{
		//if (GL_TEXTURE0 + unit == GL_TEXTURE1) {
		//	KE_CORE_INFO("IS TEXTURE 1");
		//}
		if (GL_TEXTURE0 + unit > GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS) {
			KE_CORE_ERROR("Unit index reach limit");
			return;
		}

		glActiveTexture(GL_TEXTURE0 + unit); // указывается перечислитель GL_TEXTURE0 + n
		glBindTexture(GL_TEXTURE_2D, m_TextureId);

		//glBindTextureUnit(unit, m_TextureId); // unit - индекс текстурного юнита
	}

}

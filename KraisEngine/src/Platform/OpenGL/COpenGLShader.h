#pragma once

#include <glad/glad.h>

#include <KraisEngine/Render/CShader.h>

namespace KE {
	class COpenGLShader : public CShader
	{
	public:

		COpenGLShader(std::string name, const char* vert_data, const char* frag_data);

		virtual void Bind() const;
		virtual void Unbind() const;


		virtual void SetFloat(const char* name, float f);


		virtual void SetMatrix4f(const char* name, glm::mat4& mat);

	protected:
		unsigned int m_ProgramID;
		std::string m_Name;
	protected:
		virtual GLint Compile(const char* vert, const char* frag);
		GLuint AddShader(const char* data, GLenum type);
	};
}




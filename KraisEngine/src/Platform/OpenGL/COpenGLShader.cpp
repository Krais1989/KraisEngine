//#include <KraisEngine/Core/Log.h>

#include "COpenGLShader.h"

#include <glad/glad.h>

#include <glm/gtc/type_ptr.hpp>

KE::COpenGLShader::COpenGLShader(std::string name, const char* vert_data, const char* frag_data)
	:m_Name(name)
{
	KE_CORE_INFO("CTOR>>> OpenGL Shader");

	Compile(vert_data, frag_data);
}

GLint KE::COpenGLShader::Compile(const char* vert_data, const char* frag_data)
{
	KE_CORE_INFO("Vertex shader:\n{0}", vert_data);
	KE_CORE_INFO("Fragment shader:\n{0}", frag_data);

	m_ProgramID = glCreateProgram();

	auto vert = AddShader(vert_data, GL_VERTEX_SHADER);
	auto frag = AddShader(frag_data, GL_FRAGMENT_SHADER);

	glLinkProgram(m_ProgramID);
	glDeleteShader(vert);
	glDeleteShader(frag);

	/*glDetachShader(m_ProgramID, vert);
	glDetachShader(m_ProgramID, frag);*/

	GLint isLinked;

	glGetProgramiv(m_ProgramID, GL_LINK_STATUS, &isLinked);
	if (isLinked == GL_FALSE) {
		GLint maxLen = 0;
		glGetProgramiv(m_ProgramID, GL_INFO_LOG_LENGTH, &maxLen);
		std::vector<GLchar> infoLog(maxLen);
		glGetProgramInfoLog(m_ProgramID, maxLen, &maxLen, &infoLog[0]);

		KE_CORE_ERROR("{0}", infoLog.data());
		return GL_FALSE;
	}

	return isLinked;
}

void KE::COpenGLShader::Bind() const
{
	glUseProgram(m_ProgramID);
}

void KE::COpenGLShader::Unbind() const
{
	glUseProgram(0);
}


void KE::COpenGLShader::SetFloat(const char* name, float f)
{
	GLint loc = glGetUniformLocation(m_ProgramID, name);
	glUniform1f(loc, f);
}

void KE::COpenGLShader::SetMatrix4f(const char* name, glm::mat4& mat)
{
	GLint loc = glGetUniformLocation(m_ProgramID, name);
	glUniformMatrix4fv(loc, 1, GL_FALSE, glm::value_ptr(mat));
}

void KE::COpenGLShader::SetInt(const char* name, int i)
{
	GLint loc = glGetUniformLocation(m_ProgramID, name);
	glUniform1i(loc, i);
}

void KE::COpenGLShader::SetVector4f(const char* name, glm::vec4& vec)
{
	GLint loc = glGetUniformLocation(m_ProgramID, name);
	glUniform4fv(loc, 1, glm::value_ptr(vec));
}

GLuint KE::COpenGLShader::AddShader(const char* data, GLenum type)
{
	GLuint shaderId;
	shaderId = glCreateShader(type);
	glShaderSource(shaderId, 1, &data, nullptr);
	glCompileShader(shaderId);

	GLint isCompiled = 0;
	glGetShaderiv(shaderId, GL_COMPILE_STATUS, &isCompiled);

	if (isCompiled == GL_FALSE) {
		GLint maxLen = 0;
		glGetShaderiv(shaderId, GL_INFO_LOG_LENGTH, &maxLen);
		std::vector<GLchar> infoLog(maxLen);
		glGetShaderInfoLog(shaderId, maxLen, &maxLen, &infoLog[0]);
		glDeleteShader(shaderId);
		KE_CORE_ERROR("{0}", infoLog.data());
		return 0;
	}
	else {
		glAttachShader(m_ProgramID, shaderId);
		return shaderId;
	}
}

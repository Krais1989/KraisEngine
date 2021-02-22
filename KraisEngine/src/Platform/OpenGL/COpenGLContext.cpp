#include "COpenGLContext.h"

namespace KE
{
	COpenGLContext::COpenGLContext(GLFWwindow* window)
		:m_Window(window)
	{
	}

	void COpenGLContext::Init()
	{
		glfwMakeContextCurrent(m_Window);
		int gladInitRes = gladLoadGL();
		//glEnable(GL_DEPTH_TEST);
		KE_CORE_ASSERT(gladInitRes, "GLAD Initialization error");

		glEnable(GL_DEPTH_TEST);
		glDepthFunc(GL_ALWAYS);
	}

	void COpenGLContext::SwapBuffer()
	{
		glfwSwapBuffers(m_Window);
	}

	void COpenGLContext::Clear()
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		//glClear(GL_COLOR_BUFFER_BIT);
	}

	void COpenGLContext::SetClearColor(float r, float g, float b, float a)
	{
		glClearColor(r, g, b, a);
	}

}

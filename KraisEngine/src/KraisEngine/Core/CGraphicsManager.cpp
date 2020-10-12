#include "ke_pch.h"
#include "CGraphicsManager.h"

namespace KE {

	CGraphicsManager::~CGraphicsManager()
	{
		if (m_window != nullptr)
			glfwDestroyWindow(m_window);
		glfwTerminate();
	}

	int CGraphicsManager::Initialize(const InitData& initData)
	{
		if (!glfwInit()) {
			return -1;
		}

		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

		m_window = glfwCreateWindow(initData.Width, initData.Height, initData.Title, nullptr, nullptr);
		if (!m_window) {
			glfwTerminate();
			return -1;
		}

		glfwMakeContextCurrent(m_window);

		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
		{
			std::cout << "Failed to initialize OpenGL context" << std::endl;
			return -1;
		}


		//gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);

		return 0;
	}

	bool CGraphicsManager::ShouldClose()
	{
		return glfwWindowShouldClose(m_window);
	}

	void CGraphicsManager::PollEvents()
	{
		glfwPollEvents();
	}

	void CGraphicsManager::SwapBuffers()
	{
		glfwSwapBuffers(m_window);
	}

	void CGraphicsManager::ClearScreen()
	{
		glClear(GL_COLOR_BUFFER_BIT);
	}

	void CGraphicsManager::ClearColor(float r, float g, float b, float a)
	{
		glClearColor(r, g, b, a);
	}

	void CGraphicsManager::SetViewport(int ox, int oy, int width, int height)
	{
		glViewport(ox, oy, width, height);
	}


}
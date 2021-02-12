#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "KraisEngine/Core/Core.h"
#include "KraisEngine/Render/CGraphicsContext.h"


class GLFWwindow;

namespace KE
{
	class COpenGLContext : public CGraphicsContext
	{
	public:
		COpenGLContext(GLFWwindow* window);

		virtual void Init();
		virtual void SwapBuffer();
		virtual void Clear();
		virtual void SetClearColor(float r, float g, float b, float a);
	protected:
		GLFWwindow* m_Window;
	};
}

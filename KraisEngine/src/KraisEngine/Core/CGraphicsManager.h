#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace KE {
	class CGraphicsManager
	{

	public:
		struct InitData {
			int Width;
			int Height;
			const char* Title;
		};

	private:

		GLFWwindow* m_window;

	public:

		virtual ~CGraphicsManager();

		int Initialize(const InitData& initData);
		
		bool ShouldClose();
		void PollEvents();
		void SwapBuffers();
		void ClearScreen();
		void ClearColor(float r, float g, float b, float a);

		void SetViewport(int ox, int oy, int width, int height);
	};
}



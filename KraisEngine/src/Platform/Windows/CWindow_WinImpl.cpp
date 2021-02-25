
#include "CWindow_WinImpl.h"

#include <KraisEngine/Events/WindowEvents.h>
#include <KraisEngine/Events/KeyEvents.h>
#include <KraisEngine/Events/MouseEvents.h>

#include "Platform/OpenGL/COpenGLContext.h"

//#include <imgui.h>
//#include <backends/imgui_impl_glfw.h>
//#include <backends/imgui_impl_opengl3.h>

namespace KE
{
	static bool m_GLFWInitialized = false;

	CWindow* CWindow::Create(const SWindowInitData& data /* = SWindowData() */) {
		return new CWindow_WinImpl(data);
	}

	CWindow_WinImpl::CWindow_WinImpl(const SWindowInitData& data)
	{
		Init(data);
	}

	CWindow_WinImpl::~CWindow_WinImpl()
	{
		Shutdown();
	}

	const std::string& CWindow_WinImpl::GetTitle() const
	{
		return m_Data.Title;
	}

	unsigned int CWindow_WinImpl::GetWidth() const
	{
		return m_Data.Width;
	}

	unsigned int CWindow_WinImpl::GetHeight() const
	{
		return m_Data.Height;
	}

	void CWindow_WinImpl::SetVSync(bool enable)
	{
		glfwSwapInterval(enable ? 1 : 0);
		m_Data.VSync = enable;
	}

	bool CWindow_WinImpl::IsVSyncEnabled() const
	{
		return m_Data.VSync;
	}

	void CWindow_WinImpl::SetEventCallback(const EventCallbackFn& evCallback)
	{
		m_Data.EventCallback = evCallback;
	}


	void CWindow_WinImpl::SetCursorEnabled(bool val)
	{
		glfwSetInputMode(m_Window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	}

	void CWindow_WinImpl::SetTitle(const char* title)
	{
		glfwSetWindowTitle(m_Window, title);
		m_Data.Title = std::string(title);
	}

	void CWindow_WinImpl::GetPosition(int* xpos, int* ypos)
	{
		glfwGetWindowPos(m_Window, xpos, ypos);
	}

	void CWindow_WinImpl::SetPosition(int xpos, int ypos)
	{
		glfwSetWindowPos(m_Window, xpos, ypos);
	}

	void CWindow_WinImpl::GetSize(int* width, int* height)
	{
		glfwGetWindowSize(m_Window, width, height);
	}

	void CWindow_WinImpl::SetSize(int width, int height)
	{
		glfwSetWindowSize(m_Window, width, height);
		m_Data.Width = width;
		m_Data.Height = height;
	}

	void CWindow_WinImpl::SetMaxSize(int min_width, int min_height, int max_width, int max_height)
	{
		glfwSetWindowSizeLimits(m_Window, min_width, min_height, max_width, max_height);
	}

	float CWindow_WinImpl::GetOpacity()
	{
		return glfwGetWindowOpacity(m_Window);
	}

	void CWindow_WinImpl::SetOpacity(float opacity)
	{
		glfwSetWindowOpacity(m_Window, opacity);
	}

	void CWindow_WinImpl::Minimize()
	{
		glfwIconifyWindow(m_Window);
	}

	void CWindow_WinImpl::Maximize()
	{
		glfwMaximizeWindow(m_Window);
	}

	void CWindow_WinImpl::Restore()
	{
		glfwRestoreWindow(m_Window);
	}

	void CWindow_WinImpl::Show()
	{
		glfwShowWindow(m_Window);
	}

	void CWindow_WinImpl::Hide()
	{
		glfwHideWindow(m_Window);
	}

	void CWindow_WinImpl::Focus()
	{
		glfwFocusWindow(m_Window);
	}

	void CWindow_WinImpl::RequestAttention()
	{
		glfwRequestWindowAttention(m_Window);
	}

	void CWindow_WinImpl::Init(const SWindowInitData& prop)
	{
		m_Data.Title = prop.Title;
		m_Data.Width = prop.Width;
		m_Data.Height = prop.Height;

		KE_CORE_INFO("Creating Window_WinImpl {0} ({1}, {2}) ", prop.Title, prop.Width, prop.Height);

		if (!m_GLFWInitialized) {
			int initResult = glfwInit();
			KE_CORE_ASSERT(initResult, "GLFW Initialization error");

			//typedef void (* GLFWerrorfun)(int,const char*);
			glfwSetErrorCallback([](int err_code, const char* msg) {
				KE_CORE_ERROR("GLFW ERROR: CODE({0}) Message: {1}", err_code, msg);
				});
			m_GLFWInitialized = true;
		}

		m_Window = glfwCreateWindow(m_Data.Width, m_Data.Height, m_Data.Title.c_str(), nullptr, nullptr);

		m_GraphicsContext = CGraphicsContext::Create(m_Window);
		m_GraphicsContext->Init();

		SetVSync(true);

		glfwSetWindowUserPointer(m_Window, &m_Data);

		glfwSetFramebufferSizeCallback(m_Window, [](GLFWwindow* win, int width, int height) {
			SWindowData& data = *(SWindowData*)glfwGetWindowUserPointer(win);
			data.Width = width;
			data.Height = height;
			});

		glfwSetWindowSizeCallback(m_Window, [](GLFWwindow* win, int width, int height) {
			SWindowData& data = *(SWindowData*)glfwGetWindowUserPointer(win);
			data.Width = width;
			data.Height = height;

			data.EventCallback(CWindowResizeEvent(width, height));
			});

		glfwSetWindowCloseCallback(m_Window, [](GLFWwindow* win) {
			SWindowData& data = *(SWindowData*)glfwGetWindowUserPointer(win);
			data.EventCallback(CWindowCloseEvent());
			});

		glfwSetCharCallback(m_Window, [](GLFWwindow* win, unsigned int code) {
			SWindowData& data = *(SWindowData*)glfwGetWindowUserPointer(win);
			data.EventCallback(CKeyTypedEvent(code));
			});

		glfwSetKeyCallback(m_Window, [](GLFWwindow* win, int key, int scancode, int action, int modif) {
			SWindowData& data = *(SWindowData*)glfwGetWindowUserPointer(win);
			switch (action)
			{
			case GLFW_PRESS:
				data.EventCallback(CKeyPressedEvent(key));
				break;
			case GLFW_RELEASE:
				data.EventCallback(CKeyReleasedEvent(key));
				break;
				/*case GLFW_REPEAT:
					data.EventCallback(CKeyRepeatedEvent(key));
					break;*/
			default:
				break;
			}
			});

		glfwSetMouseButtonCallback(m_Window, [](GLFWwindow* win, int btn, int action, int modif) {
			SWindowData& data = *(SWindowData*)glfwGetWindowUserPointer(win);
			switch (action)
			{
			case GLFW_PRESS:
				data.EventCallback(CMouseButtonPressedEvent(btn));
				break;
			case GLFW_RELEASE:
				data.EventCallback(CMouseButtonReleasedEvent(btn));
				break;
			default:
				break;
			}
			});

		glfwSetScrollCallback(m_Window, [](GLFWwindow* win, double xo, double yo) {
			SWindowData& data = *(SWindowData*)glfwGetWindowUserPointer(win);
			data.EventCallback(CMouseScrollEvent((float)xo, (float)yo));
			});

		glfwSetCursorPosCallback(m_Window, [](GLFWwindow* win, double mx, double my) {
			SWindowData& data = *(SWindowData*)glfwGetWindowUserPointer(win);
			data.EventCallback(CMouseMoveEvent((float)mx, (float)my));
			});
	}

	void CWindow_WinImpl::Render()
	{
		glfwSwapBuffers(m_Window);
	}

	void CWindow_WinImpl::PoolEvents()
	{
		glfwPollEvents();
	}

	void CWindow_WinImpl::Shutdown()
	{
		if (m_Window)
			glfwDestroyWindow(m_Window);

		glfwTerminate();
	}

}

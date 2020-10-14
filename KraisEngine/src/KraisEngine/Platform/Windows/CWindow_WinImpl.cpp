
#include <ke_pch.h>
#include "CWindow_WinImpl.h"

#include <KraisEngine/Events/WindowEvents.h>
#include <KraisEngine/Events/KeyEvents.h>
#include <KraisEngine/Events/MouseEvents.h>

namespace KE
{
	static bool m_GLFWInitialized = false;

	CWindow* CWindow::Create(const SWindowProps& data /* = SWindowData() */) {
		return new CWindow_WinImpl(data);
	}


	CWindow_WinImpl::CWindow_WinImpl(const SWindowProps& data)
	{
		Init(data);
	}

	CWindow_WinImpl::~CWindow_WinImpl()
	{
		Shutdown();
	}

	void CWindow_WinImpl::OnUpdate()
	{
		glfwPollEvents();
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

	void CWindow_WinImpl::Init(const SWindowProps& prop)
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
		glfwMakeContextCurrent(m_Window);
		glfwSetWindowUserPointer(m_Window, &m_Data);
		SetVSync(true);

		// (* GLFWwindowsizefun)(GLFWwindow*,int,int);
		glfwSetWindowSizeCallback(m_Window, [](GLFWwindow* win, int width, int height) {
			SWindowData& data = *(SWindowData*)glfwGetWindowUserPointer(win);
			data.Width = width;
			data.Height = height;

			data.EventCallback(CWindowResizeEvent(width, height));
			});

		//typedef void (* GLFWwindowclosefun)(GLFWwindow*);
		glfwSetWindowCloseCallback(m_Window, [](GLFWwindow* win) {
			SWindowData& data = *(SWindowData*)glfwGetWindowUserPointer(win);
			data.EventCallback(CWindowCloseEvent());
			});

		//typedef void (* GLFWkeyfun)(GLFWwindow*,int,int,int,int);
		glfwSetKeyCallback(m_Window, [](GLFWwindow* win, int key, int scancode, int action, int modif) {
			SWindowData& data = *(SWindowData*)glfwGetWindowUserPointer(win);

			switch (action)
			{
			case GLFW_PRESS:
				data.EventCallback(CKeyPressedEvent(key, 0));
				break;
			case GLFW_RELEASE:
				data.EventCallback(CKeyReleasedEvent(key));
				break;
			case GLFW_REPEAT:
				data.EventCallback(CKeyPressedEvent(key, 1));
				break;
			default:
				break;
			}
			});

		//typedef void (* GLFWmousebuttonfun)(GLFWwindow*,int,int,int);

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

		// typedef void (* GLFWscrollfun)(GLFWwindow*,double,double);

		glfwSetScrollCallback(m_Window, [](GLFWwindow* win, double xo, double yo) {
			SWindowData& data = *(SWindowData*)glfwGetWindowUserPointer(win);
			data.EventCallback(CMouseScrollEvent((float)xo, (float)yo));
			});

		// typedef void (* GLFWcharfun)(GLFWwindow*,unsigned int);
		glfwSetCharCallback(m_Window, [](GLFWwindow* win, unsigned int code) {
			SWindowData& data = *(SWindowData*)glfwGetWindowUserPointer(win);
			data.EventCallback(CKeyTypedEvent(code));
			});

		// typedef void (* GLFWcursorposfun)(GLFWwindow*,double,double);
		glfwSetCursorPosCallback(m_Window, [](GLFWwindow* win, double mx, double my) {
			SWindowData& data = *(SWindowData*)glfwGetWindowUserPointer(win);
			data.EventCallback(CMouseMoveEvent(mx, my));
			});

	}

	void CWindow_WinImpl::Shutdown()
	{
		if (m_Window)
			glfwDestroyWindow(m_Window);

		glfwTerminate();
	}

}

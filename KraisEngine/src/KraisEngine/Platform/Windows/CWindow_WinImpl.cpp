
#include <ke_pch.h>
#include "CWindow_WinImpl.h"

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
			m_GLFWInitialized = true;
		}

		m_Window = glfwCreateWindow(m_Data.Width, m_Data.Height, m_Data.Title.c_str(), nullptr, nullptr);
		glfwMakeContextCurrent(m_Window);
		glfwSetWindowUserPointer(m_Window, &m_Data);
		SetVSync(true);

		// (* GLFWwindowsizefun)(GLFWwindow*,int,int);
		glfwSetWindowSizeCallback(m_Window, [](GLFWwindow* win, int width, int height) {
			SWindowData& data = *(SWindowData*)glfwGetWindowUserPointer(win);
			data.EventCallback(CWindowResizeEvent(width, height));
		});

		//typedef void (* GLFWwindowclosefun)(GLFWwindow*);
		glfwSetWindowCloseCallback(m_Window, [](GLFWwindow* win) {
			SWindowData& data = *(SWindowData*)glfwGetWindowUserPointer(win);
			data.EventCallback(CWindowCloseEvent());
		});
	}

	void CWindow_WinImpl::Shutdown()
	{
		if (m_Window)
			glfwDestroyWindow(m_Window);

		glfwTerminate();
	}

}

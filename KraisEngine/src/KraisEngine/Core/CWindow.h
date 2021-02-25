#pragma once

#include <KraisEngine/Core/Core.h>
#include <KraisEngine/Events/CEvent.h>

namespace KE {

	struct KE_API SWindowInitData {
		std::string Title;
		unsigned int Width;
		unsigned int Height;

		SWindowInitData(const std::string& title = "Krais Engine",
			unsigned int width = 1280,
			unsigned int height = 720
		) : Title(title), Width(width), Height(height)
		{
		}
	};

	class KE_API CWindow
	{
	protected:
	public:


		virtual ~CWindow() = default;

		virtual void* GetInternalWindowObject() = 0;

		virtual unsigned int GetWidth() const = 0;
		virtual unsigned int GetHeight() const = 0;


		virtual const std::string& GetTitle() const = 0;

		virtual void SetTitle(const char* title) {
			//glfwSetWindowTitle(GLFWwindow * window, const char* title);
		}
		virtual void SetIcon(const void* icons, int count) {
			//glfwSetWindowIcon(GLFWwindow* window, int count, const GLFWimage* images);
		}
		virtual void GetPosition(int* xpos, int* ypos) {
			//glfwGetWindowPos(GLFWwindow* window, int* xpos, int* ypos);
		}
		virtual void SetPosition(int xpos, int ypos) {
			//glfwSetWindowPos(GLFWwindow * window, int xpos, int ypos);
		}
		virtual void GetSize(int* width, int* height) {
			//glfwGetWindowSize(GLFWwindow * window, int* width, int* height);
		}
		virtual void SetSize(int width, int height) {
			//glfwSetWindowSize(GLFWwindow* window, int width, int height);
		}
		virtual void SetMaxSize(int min_width, int min_height, int max_width, int max_height) {
			//glfwSetWindowSizeLimits(GLFWwindow * window, int minwidth, int minheight, int maxwidth, int maxheight);
		}

		/// <summary>
		/// ������������ ������
		/// </summary>
		virtual float GetOpacity() { /*glfwGetWindowOpacity(GLFWwindow * window);*/ return 1.0f; }
		/// <summary>
		/// ���������� ������������ ������
		/// </summary>
		virtual void SetOpacity(float opacity){ /*glfwSetWindowOpacity(GLFWwindow * window, float opacity);*/ }

		/// <summary>
		/// �������� ����
		/// </summary>
		virtual void Minimize(){ /* glfwIconifyWindow(GLFWwindow * window) */ }
		/// <summary>
		/// ���������� �� ���� �����
		/// </summary>
		virtual void Maximize() { /* glfwMaximizeWindow(GLFWwindow* window) */ }
		/// <summary>
		/// ������������ ������������/�������� ����
		/// </summary>
		virtual void Restore() { /* glfwRestoreWindow(GLFWwindow* window) */ }
		/// <summary>
		/// �������� ����
		/// </summary>
		virtual void Show() { /* glfwShowWindow(GLFWwindow* window) */ }
		/// <summary>
		/// ������ ����
		/// </summary>
		virtual void Hide() { /* glfwHideWindow(GLFWwindow* window) */ }
		/// <summary>
		/// ����� ����
		/// </summary>
		virtual void Focus() { /* glfwFocusWindow(GLFWwindow* window) */ }
		/// <summary>
		/// ����������� �������� � ���� (����. ��������� ������ ���� � Windows)
		/// </summary>
		virtual void RequestAttention() { /*glfwRequestWindowAttention(GLFWwindow* window)*/ }

		virtual void SetVSync(bool enable) { /* glfwSwapInterval(int interval) ��� interval > 0  */ };

		virtual bool IsVSyncEnabled() const { return false; };

		virtual void SetCursorEnabled(bool val) = 0;

	protected:
		friend class CApplication;

		/// <summary>
		/// ��������������� ������� ���� (����, ����������� � ��)
		/// </summary>
		virtual void PoolEvents() = 0;

		/// <summary>
		/// ��������� ���� (Swap Buffer/Chain)
		/// </summary>
		virtual void Render() = 0;

		using EventCallbackFn = std::function<void(CEvent&)>;

		virtual void SetEventCallback(const EventCallbackFn& evCallback) = 0;

		/// <summary>
		/// ��������� ����� �������� ����
		/// ����������� ��� ������ ��������� � ��������������� ������
		/// </summary>
		static CWindow* Create(const SWindowInitData& data = SWindowInitData());
	};
}




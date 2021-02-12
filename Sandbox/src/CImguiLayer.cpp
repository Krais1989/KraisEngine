#include "CImguiLayer.h"

#include <imgui.h>
#include <backends/imgui_impl_glfw.h>
#include <backends/imgui_impl_opengl3.h>

namespace KE
{
	void CImguiLayer::OnAttach()
	{
		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO(); (void)io;
		//io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
		//io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

		// Setup Dear ImGui style
		ImGui::StyleColorsDark();
		//ImGui::StyleColorsClassic();

		// Setup Platform/Renderer backends
		//ImGui_ImplGlfw_InitForOpenGL(CApplication::, true);
		//ImGui_ImplOpenGL3_Init(glsl_version);


		throw std::logic_error("The method or operation is not implemented.");
	}
	
	void CImguiLayer::OnDetach()
	{
		throw std::logic_error("The method or operation is not implemented.");
	}
	
	void CImguiLayer::OnUpdate(float dt)
	{
		throw std::logic_error("The method or operation is not implemented.");
	}
	
	void CImguiLayer::OnEvent(CEvent& ev)
	{
		throw std::logic_error("The method or operation is not implemented.");
	}
}

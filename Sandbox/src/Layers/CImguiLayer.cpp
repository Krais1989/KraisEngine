#include "CImguiLayer.h"

#include <imgui.h>
#include <backends/imgui_impl_glfw.h>
#include <backends/imgui_impl_opengl3.h>


CImguiLayer::CImguiLayer()
{
	IMGUI_CHECKVERSION();
	auto* ctx = ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;

	//io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
	//io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

	// Setup Dear ImGui style
	ImGui::StyleColorsDark();
	//ImGui::StyleColorsClassic();

	// Setup Platform/Renderer backends
	//ImGui_ImplGlfw_InitForOpenGL(CApplication::, true);
	//ImGui_ImplOpenGL3_Init(glsl_version);

	KE::CApplication& app = KE::CApplication::Get();
	GLFWwindow* window = static_cast<GLFWwindow*>(app.GetWindow()->GetWindowObject());

	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init("#version 460");
}

//
//#include <GLFW/glfw3.h>
//#include <glad/glad.h>

void CImguiLayer::OnAttach()
{

}

void CImguiLayer::OnDetach()
{
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
}

void CImguiLayer::OnUpdate(float dt)
{
}

void CImguiLayer::OnEvent(KE::CEvent& ev)
{
}

void CImguiLayer::OnRender()
{
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();

	if (m_ShowDemo)
		ImGui::ShowDemoWindow(&m_ShowDemo);

	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}
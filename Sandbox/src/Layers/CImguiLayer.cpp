#include "CImguiLayer.h"

#include <imgui.h>
#include <backends/imgui_impl_glfw.h>
#include <backends/imgui_impl_opengl3.h>


CImguiLayer::CImguiLayer()
{
	IMGUI_CHECKVERSION();
	auto* ctx = ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();

	//io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
	//io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

	// Setup Dear ImGui style
	ImGui::StyleColorsDark();
	//ImGui::StyleColorsClassic();

	// Setup Platform/Renderer backends
	//ImGui_ImplGlfw_InitForOpenGL(CApplication::, true);
	//ImGui_ImplOpenGL3_Init(glsl_version);

	KE::CApplication& app = KE::CApplication::Get();
	GLFWwindow* window = static_cast<GLFWwindow*>(app.GetWindow()->GetInternalWindowObject());

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

	ImGui::Begin("Camera Tool", &m_CameraTool, ImGuiWindowFlags_MenuBar);
	//if (ImGui::BeginMenuBar()) {
	//	if (ImGui::BeginMenu("File")) {
	//		if (ImGui::MenuItem("Open..", "Ctrl+O")) { KE_INFO("Open.."); }
	//		if (ImGui::MenuItem("Save..", "Ctrl+O")) { KE_INFO("Save.."); }
	//		if (ImGui::MenuItem("Close..", "Ctrl+O")) { KE_INFO("Close.."); }
	//	}
	//	ImGui::EndMenuBar();
	//}

	static float f = 0.0f;
	ImGui::SliderFloat("fff", &f, 0.0f, 1.0f);

	ImGui::End();

	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}
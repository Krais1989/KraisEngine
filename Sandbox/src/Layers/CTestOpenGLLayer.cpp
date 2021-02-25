
#include "CTestOpenGLLayer.h"

CTestOpenGLLayer::CTestOpenGLLayer()
	: m_CurVAO(0), m_CurShader(0), m_Time(0), m_CurTransform(0)
{	
	auto& app = KE::CApplication::Get();
	auto& window = app.GetWindow();
	auto& camController = app.GetCameraController();
	auto& cam = camController->GetCamera();

	m_TextureWall = KE::CTexture2D::Create("Assets/Textures/wall.jpg");
	m_TextureStone = KE::CTexture2D::Create("Assets/Textures/stone.jpg");

	LoadTestTransforms();
	LoadTestShaders();
	LoadTestBuffers();

	float width = window->GetWidth();
	float height = window->GetHeight();
	window->SetCursorEnabled(false);
	//m_Projection = glm::ortho(0.0f, width, 0.0f, height, 0.1f, 100.0f);
	//m_Projection = glm::perspective(glm::radians(45.0f), width / height, 0.1f, 100.0f);


	//m_CamPosition = glm::vec3(0.0f, 2.0f, 5.0f);
	//m_CamDirection = glm::vec3(0.0f, 0.0f, 0.0f);
	//m_CamUp = glm::vec3(0.0f, 1.0f, 0.0f);

	cam->SetPosition({ 0.0f, 2.0f, 5.0f });
	cam->SetForward({ 0.0f, 0.0f, -1.0f });
	cam->SetUp({ 0.0f, 1.0f, 0.0f });
	cam->UpdatePerspective(glm::radians(45.0f), width / height, 0.1f, 100.0f);

	camController->SetForwardSpeed(8.0f);
	camController->SetBackwardSpeed(8.0f);
	camController->SetSideSpeed(8.0f);
	camController->SetUpSpeed(8.0f);

	//m_Camera.UpdateView(glm::vec3(0.0f, 2.0f, 5.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));


}

void CTestOpenGLLayer::OnAttach()
{
	KE_INFO("CTestOpenGLLayer OnAttach");
}

void CTestOpenGLLayer::OnDetach()
{
	KE_INFO("CTestOpenGLLayer OnDetach");
}

void CTestOpenGLLayer::OnUpdate(float dt)
{
	//KE_INFO("CTestOpenGLLayer OnUpdate");
	auto t01 = std::fmod(m_Time, 1.0f);
	auto t010 = glm::sin(m_Time) / 2.0f + 0.5f;

	m_Time += dt;
}

void CTestOpenGLLayer::OnEvent(KE::CEvent& ev)
{
	auto& app = KE::CApplication::Get();
	auto& window = app.GetWindow();
	auto& camController = app.GetCameraController();
	auto& cam = camController->GetCamera();

	if (ev.IsInCategory(KE::EEventCategory::KE_EventCategory_Keyboard)
		&& ev.GetEventType() != KE::EEventType::KeyRepeated
		&& ev.GetEventType() != KE::EEventType::KeyTyped) {

		auto& keyEvent = reinterpret_cast<KE::CKeyEvent&>(ev);
		OnKeyEvent(keyEvent);
	}

	if (ev.IsInCategory(KE::KE_EventCategory_Mouse)) {
		if (ev.GetEventType() == KE::EEventType::MouseMoved) {
			auto& mouseEvent = reinterpret_cast<KE::CMouseMoveEvent&>(ev);
			OnMouseEvent(mouseEvent);
		}
	}

	if (ev.IsInCategory(KE::KE_EventCategory_Application)) {
		if (ev.GetEventType() == KE::EEventType::WindowResize) {
			auto& resizeEvent = reinterpret_cast<KE::CWindowResizeEvent&>(ev);

			if (cam->GetCameraType() == KE::ECameraType::Orthographic)
			{
				cam->SetOrthoMaxWidth((float)resizeEvent.Width);
				cam->SetOrthoMaxHeight((float)resizeEvent.Height);
			}
		}
	}

	if (ev.IsInCategory(KE::KE_EventCategory_Input))
		camController->OnInputEvent(ev);

}

void CTestOpenGLLayer::OnRender()
{
	auto& app = KE::CApplication::Get();
	auto& window = app.GetWindow();
	auto& camController = app.GetCameraController();
	auto& cam = camController->GetCamera();

	/* GL_FRONT || GL_BACK || GL_FRONT_AND_BACK */
	/* GL_POINT || GL_LINE || GL_FILL */
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	m_TextureWall->Bind(0);
	m_TextureStone->Bind(1);

	auto& shader = *m_Shaders[m_CurShader].get();
	shader.Bind();
	shader.SetFloat("Time", m_Time * 5.0f);
	shader.SetMatrix4f("Model", m_Models[m_CurTransform]);
	shader.SetMatrix4f("View", cam->GetViewMatrix());
	shader.SetMatrix4f("Projection", cam->GetProjectionMatrix());
	shader.SetInt("Texture_1", 0);
	shader.SetVector4f("AmbientColor", glm::vec4(0, 0, 1, 1));

	glBindVertexArray(m_VAOs[m_CurVAO]);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}


void CTestOpenGLLayer::OnKeyEvent(KE::CKeyEvent& keyEv)
{
	bool isPressed = keyEv.GetEventType() == KE::EEventType::KeyPressed;
	bool isReleased = keyEv.GetEventType() == KE::EEventType::KeyReleased;
	//bool isRepeated = keyEv.GetEventType() == KE::EEventType::KeyRepeated;
	//bool isTyped = keyEv.GetEventType() == KE::EEventType::KeyTyped;

	auto key = keyEv.GetKey();
	//KE_INFO("PRESSED:{0} RELEASED:{1} REPEATED:{2} TYPED:{3}", isPressed, isReleased, isRepeated, isTyped);
	KE_INFO("{0}: {1}", keyEv.GetEventName(), key);

	switch (key)
	{
	case KE::Key::D1:
		m_CurVAO = (m_CurVAO + 1) % m_VAOs.size();
		KE_INFO("Current VAO: [{0}] {1}", m_CurVAO, m_VAOs[m_CurVAO]);
		break;
	case KE::Key::D2:
		m_CurShader = (m_CurShader + 1) % m_Shaders.size();
		KE_INFO("Current Shader: [{0}] {1}", m_CurShader, m_Shaders[m_CurShader]->GetID());
		break;
	case KE::Key::D3:
		m_CurTransform = (m_CurTransform + 1) % m_Models.size();
		KE_INFO("Current Transform: [{0}]", m_CurTransform);
		break;
	default:
		break;
	}

	keyEv.Handled = true;
}

void CTestOpenGLLayer::OnMouseEvent(KE::CMouseMoveEvent& mouseEv)
{

}

void CTestOpenGLLayer::LoadTestShaders()
{
	//LoadShader("shader1", std::filesystem::path("Assets/Shaders/shader1.vert"), std::filesystem::path("Assets/Shaders/shader1.frag"));
	LoadShader("default", std::filesystem::path("Assets/Shaders/default.vert"), std::filesystem::path("Assets/Shaders/default.frag"));
}

void CTestOpenGLLayer::LoadTestBuffers()
{
	float verts1[] = {
	-0.5f, -0.5f, 0.0f,
	0.5f, -0.5f, 0.0f,
	0.0f, 0.5f, 0.0f,
	};
	unsigned int inds1[] = { 0,1,2 };

	float verts2[] = {
		-0.5f, 0.5f, 0.0f,
		0.0f, -0.5f, 0.0f,
		0.5f, 0.5f, 0.0f,
	};
	unsigned int inds2[] = { 0,1,2 };

	float verts3[] = {
		-0.5f, -0.5f, 0.0f,
		-0.5f, 0.5f, 0.0f,
		0.5f, 0.5f, 0.0f,
		0.5f, -0.5f, 0.0f
	};
	unsigned int inds3[] = { 0,1,3, 1,2,3 };

	float verts4[] = {
	-0.5f, -0.5f, 0.0f,	0.0f, 0.0f,
	-0.5f, 0.5f, 0.0f,	0.0f, 1.0f,
	0.5f, 0.5f, 0.0f,	1.0f, 1.0f,
	0.5f, -0.5f, 0.0f,	1.0f, 0.0f
	};
	unsigned int inds4[] = { 0,1,3, 1,2,3 };

	float fs = 10.0f;
	float verts_floor[] = {
		-fs,0.0f,-fs,	0.0f, 0.0f,
		-fs,0.0f, fs,	0.0f, 1.0f,
		fs,0.0f,fs,		1.0f, 1.0f,
		fs,0.0f,-fs,	1.0f, 0.0f
	};
	unsigned int inds_floor[] = { 0,1,3, 1,2,3 };

	//LoadBufferVertElem(verts1, 9, inds1, 3);
	//LoadBufferVertElem(verts2, 9, inds2, 3);
	//LoadBufferVertElem(verts3, 12, inds3, 6);
	//LoadBufferVertElemUV(verts4, 20, inds4, 6);
	LoadBufferVertElemUV(verts_floor, 20, inds_floor, 6);
}

void CTestOpenGLLayer::LoadShader(std::string name, fs::path vert, fs::path frag)
{
	auto shader = KE::CShader::CreateFromFile(name, vert, frag);
	m_Shaders.push_back(shader);
}

void CTestOpenGLLayer::LoadBufferVertElem(const float* verts, size_t vertsSize, const unsigned int* inds, size_t indsSize)
{
	GLuint vaoId;
	GLuint vboId;
	GLuint eboId;

	glGenVertexArrays(1, &vaoId);
	glGenBuffers(1, &vboId);
	glGenBuffers(1, &eboId);

	glBindVertexArray(vaoId);
	glBindBuffer(GL_ARRAY_BUFFER, vboId);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * vertsSize, verts, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, eboId);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * indsSize, inds, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr);
	glEnableVertexAttribArray(0);

	m_VAOs.push_back(vaoId);
}

void CTestOpenGLLayer::LoadBufferVertElemUV(const float* verts, size_t vertsSize, const unsigned int* inds, size_t indsSize)
{
	GLuint vaoId;
	GLuint vboId;
	GLuint eboId;

	glGenVertexArrays(1, &vaoId);
	glGenBuffers(1, &vboId);
	glGenBuffers(1, &eboId);

	glBindVertexArray(vaoId);
	glBindBuffer(GL_ARRAY_BUFFER, vboId);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * vertsSize, verts, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, eboId);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * indsSize, inds, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	m_VAOs.push_back(vaoId);
}

void CTestOpenGLLayer::LoadTestTransforms()
{
	{
		m_Models.push_back(glm::mat4(1.0f));
	}

	{
		auto trans = glm::translate(glm::mat4(1.0f), glm::vec3(.5f, .0f, .0f));
		auto rot = glm::rotate(glm::mat4(1.0f), glm::radians(45.0f), glm::vec3(.0f, .0f, 1.0f));
		auto scale = glm::scale(glm::mat4(1.0f), glm::vec3(1.0f));
		m_Models.push_back(trans * rot * scale);
	}

	{
		auto trans = glm::translate(glm::mat4(1.0f), glm::vec3(.5f, .0f, .0f));
		auto rot = glm::rotate(glm::mat4(1.0f), glm::radians(45.0f), glm::vec3(.0f, .0f, 1.0f));
		auto scale = glm::scale(glm::mat4(1.0f), glm::vec3(.5f, .5f, .5f));
		m_Models.push_back(trans * rot * scale);
	}

	//{
	//	auto trans = glm::translate(glm::mat4(1.0f), glm::vec3(.5f, .5f, .0f));
	//	auto rot = glm::rotate(glm::mat4(1.0f), glm::radians(22.0f), glm::vec3(.0f, .0f, 1.0f));
	//	auto scale = glm::scale(glm::mat4(1.0f), glm::vec3(.9f, .9f, .9f));
	//	m_Transforms.push_back(trans * rot * scale);
	//}

}

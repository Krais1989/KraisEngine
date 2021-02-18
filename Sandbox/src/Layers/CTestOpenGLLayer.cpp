#include "CTestOpenGLLayer.h"


CTestOpenGLLayer::CTestOpenGLLayer()
	: m_CurVAO(0), m_CurShader(0), m_Time(0), m_CurTransform(0), m_Forward(0), m_Right(0), m_Up(0)
{
	m_TextureWall = KE::CTexture2D::Create("Assets/Textures/wall.jpg");
	m_TextureStone = KE::CTexture2D::Create("Assets/Textures/stone.jpg");

	LoadTestShaders();
	LoadTestBuffers();
	LoadTestTransforms();

	float width = KE::CApplication::Get().GetWindow()->GetWidth();
	float height = KE::CApplication::Get().GetWindow()->GetHeight();
	KE::CApplication::Get().GetWindow()->SetCursorEnabled(false);
	//m_Projection = glm::ortho(0.0f, width, 0.0f, height, 0.1f, 100.0f);
	//m_Projection = glm::perspective(glm::radians(45.0f), width / height, 0.1f, 100.0f);


	//m_CamPosition = glm::vec3(0.0f, 2.0f, 5.0f);
	//m_CamDirection = glm::vec3(0.0f, 0.0f, 0.0f);
	//m_CamUp = glm::vec3(0.0f, 1.0f, 0.0f);

	m_Camera = std::make_shared<KE::CCamera>();
	m_Camera->SetPosition({ 0.0f, 2.0f, 5.0f });
	m_Camera->SetForward({ 0.0f, 0.0f, -1.0f });
	m_Camera->SetUp({ 0.0f, 1.0f, 0.0f });
	m_Camera->UpdatePerspective(glm::radians(45.0f), width / height, 0.1f, 100.0f);

	m_CameraController = std::make_shared<KE::CCameraController>();
	m_CameraController->SetCamera(m_Camera);
	m_CameraController->SetForwardSpeed(8.0f);
	m_CameraController->SetBackwardSpeed(8.0f);
	m_CameraController->SetSideSpeed(8.0f);
	m_CameraController->SetUpSpeed(8.0f);

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
	if (m_Forward != 0) {
		m_CameraController->MoveForward(m_Forward);
		//auto pos = m_Camera->GetPosition();
		//KE_INFO("Cam pos: {0}:{1}:{2}", pos[0], pos[1], pos[2]);
	}

	if (m_Right != 0) {
		m_CameraController->MoveRight(m_Right);
		//auto pos = m_Camera->GetPosition();
		//KE_INFO("Cam pos: {0}:{1}:{2}", pos[0], pos[1], pos[2]);
	}

	if (m_Up != 0) {
		m_CameraController->MoveUp(m_Up);
		//auto pos = m_Camera->GetPosition();
		//KE_INFO("Cam pos: {0}:{1}:{2}", pos[0], pos[1], pos[2]);
	}

	m_Camera->Update();
	m_CameraController->Update(dt);

	//KE_INFO("CTestOpenGLLayer OnUpdate");
	auto t01 = std::fmod(m_Time, 1.0f);
	auto t010 = glm::sin(m_Time) / 2.0f + 0.5f;

	/*auto model = glm::mat4(1.0f);
	model = glm::rotate(model, t01 * glm::two_pi<float>(), glm::vec3(0.0f, 1.0f, 0.0f));
	model = glm::scale(model, glm::vec3(1.0f));
	model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));

	m_Models[0] = model;*/

	m_Time += dt;
}



void CTestOpenGLLayer::OnEvent(KE::CEvent& ev)
{
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

			if (m_Camera->GetCameraType() == KE::ECameraType::Orthographic)
			{
				m_Camera->SetOrthoMaxWidth((float)resizeEvent.Width);
				m_Camera->SetOrthoMaxHeight((float)resizeEvent.Height);
			}
		}
	}

}

void CTestOpenGLLayer::OnRender()
{
	/* GL_FRONT || GL_BACK || GL_FRONT_AND_BACK */
	/* GL_POINT || GL_LINE || GL_FILL */
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	m_TextureWall->Bind(0);
	m_TextureStone->Bind(1);

	auto& shader = *m_Shaders[m_CurShader].get();
	shader.Bind();
	shader.SetFloat("Time", m_Time * 5.0f);
	shader.SetMatrix4f("Model", m_Models[m_CurTransform]);
	shader.SetMatrix4f("View", m_Camera->GetViewMatrix());
	shader.SetMatrix4f("Projection", m_Camera->GetProjectionMatrix());
	shader.SetInt("texture1", 0);
	shader.SetInt("texture2", 1);

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

	case KE::Key::W:
		m_Forward = isPressed ? 1 : 0;
		break;
	case KE::Key::A:
		m_Right = isPressed ? -1 : 0;
		break;
	case KE::Key::S:
		m_Forward = isPressed ? -1 : 0;
		break;
	case KE::Key::D:
		m_Right = isPressed ? 1 : 0;
		break;
	case KE::Key::R:
		m_Up = isPressed ? 1 : 0;
		break;
	case KE::Key::F:
		m_Up = isPressed ? -1 : 0;
		break;
	default:
		break;
	}

	keyEv.Handled = true;
}

void CTestOpenGLLayer::OnMouseEvent(KE::CMouseMoveEvent& mouseEv)
{
	if (m_IsFirstMouse) {
		m_LastMX = mouseEv.GetMX();
		m_LastMY = mouseEv.GetMY();
		m_IsFirstMouse = false;
	}

	float mx = mouseEv.GetMX();
	float my = mouseEv.GetMY();

	m_DeltaMX = mx - m_LastMX;
	m_DeltaMY = m_LastMY - my;
	m_LastMX = mx;
	m_LastMY = my;

	//KE_INFO("Delta mouse: ({0}:{1})", m_DeltaMX, m_DeltaMY);

	m_CameraController->AddRotationAxes(glm::vec3(m_DeltaMY, m_DeltaMX, 0));
}

void CTestOpenGLLayer::LoadTestShaders()
{
	//LoadShader("shader1", std::filesystem::path("Assets/Shaders/shader1.vert"), std::filesystem::path("Assets/Shaders/shader1.frag"));
	LoadShader("shader2", std::filesystem::path("Assets/Shaders/shader1.vert"), std::filesystem::path("Assets/Shaders/shader2.frag"));
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

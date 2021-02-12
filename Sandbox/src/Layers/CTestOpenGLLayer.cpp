#include "CTestOpenGLLayer.h"


CTestOpenGLLayer::CTestOpenGLLayer()
	: m_CurVAO(0), m_CurShader(0), m_Time(0)
{
	int width, height, nrChannels;
	unsigned char* wallTexData = stbi_load("Assets/Textures/wall.jpg", &width, &height, &nrChannels, 0);


	LoadTestShaders();
	LoadTestBuffers();
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

	//m_Model = glm::translate(glm::mat4(), glm::vec3(0.0f, 0.0f, 3.0f));
	//m_Model = glm::rotate(m_Model, glm::radians(90.0f), glm::vec3(0.0, 0.0, 1.0));
	//m_Model = glm::scale(m_Model, glm::vec3(1.0f, 1.0f, 1.0f));

	m_Time += dt;
}

void CTestOpenGLLayer::OnEvent(KE::CEvent& ev)
{
	//KE_INFO("CTestOpenGLLayer OnEvent");


	switch (ev.GetEventType())
	{
	case KE::EEventType::KeyPressed:
	{
		auto& keyPressedEvent = reinterpret_cast<KE::CKeyPressedEvent&>(ev);

		auto key = keyPressedEvent.GetKey();

		/* Смена VAO */
		switch (keyPressedEvent.GetKey())
		{
		case KE::Key::D1:
			m_CurVAO = (m_CurVAO + 1) % m_VAOs.size();
			KE_INFO("Current VAO: [{0}]", m_CurVAO);
			break;
		case KE::Key::D2:
			m_CurShader = (m_CurShader + 1) % m_Shaders.size();
			KE_INFO("Current Shader: [{0}]", m_CurShader);
			break;
		default:
			break;
		}
		break;
	}
	default:
		break;
	}
}

void CTestOpenGLLayer::OnRender()
{

	/* GL_FRONT || GL_BACK || GL_FRONT_AND_BACK */
	/* GL_POINT || GL_LINE || GL_FILL */
	// glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	m_Shaders[m_CurShader]->Bind();
	m_Shaders[m_CurShader]->SetFloat("Time", m_Time);
	//m_Shaders[m_CurShader]->SetMatrix4f("MVP", m_Projection * m_View * m_Model);
	m_Shaders[m_CurShader]->SetMatrix4f("MVP", m_Model);

	glBindVertexArray(m_VAOs[m_CurVAO]);

	// >> TEXTURE WRAPPING: GL_REPEAT, GL_MIRRORED_REPEAT, GL_CLAMP_TO_EDGE, GL_CLAMP_TO_BORDER
	// glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
	// >> TEXTURE FILTERING: GL_NEAREST, GL_LINEAR, 
	// glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST or GL_LINEAR);


	//glDrawArrays(GL_TRIANGLES, 0, 3); - не подходит при использовании индексного буффера
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	//glBindVertexArray(0);
}


void CTestOpenGLLayer::LoadTestShaders()
{
	LoadShader("shader1", std::filesystem::path("Assets/Shaders/shader1.vert"), std::filesystem::path("Assets/Shaders/shader1.frag"));
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

	float uvs1[] = {
		0.0f, 0.0f,
		0.5f, 1.0f,
		1.0f, 0.0f
	};


	LoadBuffer(verts1, 9, inds1, 3);
	LoadBuffer(verts2, 9, inds2, 3);
	LoadBuffer(verts3, 12, inds3, 6);
}

void CTestOpenGLLayer::LoadShader(std::string name, fs::path vert, fs::path frag)
{
	auto shader = KE::CShader::CreateFromFile(name, vert, frag);
	m_Shaders.push_back(shader);
}

void CTestOpenGLLayer::LoadBuffer(const float* verts, size_t vertsSize, const unsigned int* inds, size_t indsSize)
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

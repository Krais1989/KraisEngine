#pragma once

#include "KraisEngine.h"

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <stb_image.h>

namespace fs = std::filesystem;

class CTestOpenGLLayer : public KE::CLayer
{
public:

	CTestOpenGLLayer();

	virtual void OnAttach();
	virtual void OnDetach();
	virtual void OnUpdate(float dt);
	virtual void OnEvent(KE::CEvent& ev);
	virtual void OnRender();

protected:

	std::vector<GLuint> m_VAOs;
	//std::vector<GLuint> m_VBOs;
	std::vector<std::shared_ptr<KE::CShader>> m_Shaders;
	std::vector<glm::mat4> m_Models;

	size_t m_CurVAO;
	size_t m_CurShader;
	size_t m_CurTransform;

	float m_Forward;
	float m_Right;
	float m_Up;


	//glm::mat4 m_View;
	//glm::mat4 m_Projection;
	//glm::vec3 m_CamPosition;
	//glm::vec3 m_CamUp;
	//glm::vec3 m_CamDirection;

protected:

	void OnKeyEvent(KE::CKeyEvent& keyEv);

	void LoadTestShaders();
	void LoadTestBuffers();

	void LoadShader(std::string name, fs::path vert, fs::path frag);
	void LoadBufferVertElem(const float* verts, size_t vertsSize, const unsigned int* inds, size_t indsSize);
	void LoadBufferVertElemUV(const float* verts, size_t vertsSize, const unsigned int* inds, size_t indsSize);

	void LoadTestTransforms();
private:
	float m_Time;

	KE::CCamera m_Camera;


	std::shared_ptr<KE::CTexture2D> m_TextureWall;
	std::shared_ptr<KE::CTexture2D> m_TextureStone;

};

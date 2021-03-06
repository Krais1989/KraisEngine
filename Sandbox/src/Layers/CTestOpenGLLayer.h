#pragma once

#include "KraisEngine.h"

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace fs = std::filesystem;
using namespace KE;

class CTestOpenGLLayer : public CLayer
{
public:

	CTestOpenGLLayer();

	virtual void OnAttach();
	virtual void OnDetach();
	virtual void OnUpdate(float dt);
	virtual void OnEvent(CEvent& ev);
	virtual void OnRender();

protected:

	//CPlatformFactory<CVertexBuffer> m_VertexBufferFactory;
	//CPlatformFactory<CIndexBuffer> m_IndexBufferFactory;
	//CPlatformFactory<CArrayBuffer> m_ArrayBufferFactory;

	//std::vector<CArrayBuffer> m_VAOs;
	std::vector<std::shared_ptr<CShader>> m_Shaders;
	std::vector<glm::mat4> m_Models;

	size_t m_CurVAO;
	size_t m_CurShader;
	size_t m_CurTransform;

protected:

	void OnKeyEvent(CKeyEvent& keyEv);
	void OnMouseEvent(CMouseMoveEvent& mouseEv);

	void LoadTestTransforms();
	void LoadTestShaders();
	void LoadTestBuffers();

	void LoadShader(std::string name, fs::path vert, fs::path frag);
	void LoadBufferVertElemUV(const std::vector<float>& verts, const std::vector<unsigned int>& inds);


private:
	float m_Time;
	std::shared_ptr<CTexture2D> m_TextureWall;
	std::shared_ptr<CTexture2D> m_TextureStone;

};

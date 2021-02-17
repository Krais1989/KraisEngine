#include "CCameraController.h"

namespace KE {

	CCameraController::CCameraController() :
		m_ForwardSpeed(1.0f),
		m_BackwardSpeed(1.0f),
		m_SideSpeed(1.0f),
		m_UpSpeed(1.0f),
		m_Forward(0.0f),
		m_Right(0.0f), 
		m_Up(0.0f)
	{

	}

	void CCameraController::SetCamera(const std::shared_ptr<CCamera>& camera)
	{
		m_Camera = camera;
	}

	std::shared_ptr<CCamera>& CCameraController::GetCamera()
	{
		return m_Camera;
	}

	void CCameraController::MoveForward(float forward)
	{
		m_Forward = forward;
	}

	void CCameraController::MoveRight(float right)
	{
		m_Right = right;
	}

	void CCameraController::MoveUp(float up)
	{
		m_Up = up;
	}

	void CCameraController::Update(float dt)
	{
		if (m_Forward != 0) {
			m_Camera->AddPosition(m_Camera->GetForward() * glm::sign(m_Forward) * (m_Forward > 0.0f ? m_ForwardSpeed : m_BackwardSpeed) * dt);
		}

		if (m_Right != 0) {
			m_Camera->AddPosition(m_Camera->GetRight() * glm::sign(m_Right) * m_SideSpeed * dt);
		}

		if (m_Up != 0) {
			m_Camera->AddPosition(m_Camera->GetUp() * glm::sign(m_Up) * m_UpSpeed * dt);
		}

		m_Up = 0.0f;
		m_Right = 0.0f;
		m_Forward = 0.0f;
	}

}

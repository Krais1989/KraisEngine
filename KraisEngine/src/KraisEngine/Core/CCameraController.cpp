#include <ke_pch.h>

#include "CCameraController.h"

namespace KE {

	void CCameraController::OnInputEvent(CEvent& ev)
	{
		if (ev.IsInCategory(KE_EventCategory_Input)) {
			if (ev.IsInCategory(KE_EventCategory_Keyboard)
				&& (ev.GetEventType() == EEventType::KeyPressed || ev.GetEventType() == EEventType::KeyReleased))
			{
				auto& keyEvent = reinterpret_cast<CKeyEvent&>(ev);

				auto key = keyEvent.GetKey();
				bool isPressed = keyEvent.GetEventType() == KE::EEventType::KeyPressed;

				KE_INFO("CameraController> CKeyEvent: {0} {1}", keyEvent.GetEventName(), key);

				switch (key)
				{
				case KE::Key::W:
					MoveForward(isPressed ? 1.0f : 0.0f);
					break;
				case KE::Key::S:
					MoveForward(isPressed ? -1.0f : 0.0f);
					break;
				case KE::Key::D:
					MoveRight(isPressed ? 1.0f : 0.0f);
					break;
				case KE::Key::A:
					MoveRight(isPressed ? -1.0f : 0.0f);
					break;
				case KE::Key::SPACE:
					MoveUp(isPressed ? 1.0f : 0.0f);
					break;
				case KE::Key::LEFT_CONTROL:
					MoveUp(isPressed ? -1.0f : 0.0f);
					break;
				default:
					break;
				}
			}

			if (ev.IsInCategory(KE_EventCategory_Mouse)) {
				auto& mouseEv = reinterpret_cast<CMouseMoveEvent&>(ev);
				if (m_IsFirstMouse) {
					m_LastMX = mouseEv.GetMX();
					m_LastMY = mouseEv.GetMY();
					m_IsFirstMouse = false;
				}

				float mx = mouseEv.GetMX();
				float my = mouseEv.GetMY();

				float m_DeltaMX = mx - m_LastMX;
				float m_DeltaMY = m_LastMY - my;
				m_LastMX = mx;
				m_LastMY = my;
				//KE_INFO("Delta mouse: ({0}:{1})", m_DeltaMX, m_DeltaMY);
				AddRotationAxes(glm::vec3(m_DeltaMY, m_DeltaMX, 0));
			}
		}

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
		m_Camera->Update();

		if (m_Forward != 0) {
			m_Camera->AddPosition(m_Camera->GetForward() * glm::sign(m_Forward) * (m_Forward > 0.0f ? m_ForwardSpeed : m_BackwardSpeed) * dt);
		}

		if (m_Right != 0) {
			m_Camera->AddPosition(m_Camera->GetRight() * glm::sign(m_Right) * m_SideSpeed * dt);
		}

		if (m_Up != 0) {
			m_Camera->AddPosition(m_Camera->GetUp() * glm::sign(m_Up) * m_UpSpeed * dt);
		}

		//m_Forward = 0;
		//m_Right = 0;
		//m_Up = 0;
	}

	void CCameraController::AddRotationAxes(glm::vec3 rawRotAxes)
	{
		m_Camera->AddRotationAxes(rawRotAxes * m_LookSensivity);
	}

}

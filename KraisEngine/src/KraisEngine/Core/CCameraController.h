#pragma once

#include <ke_pch.h>
#include <KraisEngine.h>


namespace KE {

	class CCamera;

	class CCameraController
	{
	protected:

		std::shared_ptr<CCamera> m_Camera;

		float m_ForwardSpeed;
		float m_BackwardSpeed;
		float m_SideSpeed;
		float m_UpSpeed;
		float m_LookSensivity;

		float m_Forward;
		float m_Right;
		float m_Up;

		bool m_IsFirstMouse;
		float m_LastMX;
		float m_LastMY;

		bool m_IsForwardPressed = false;
		bool m_IsBackwardPressed = false;
		bool m_IsRightPressed = false;
		bool m_IsLeftPressed = false;


	public:

		CCameraController() :
			m_ForwardSpeed(1.0f),
			m_BackwardSpeed(1.0f),
			m_SideSpeed(1.0f),
			m_UpSpeed(1.0f),
			m_LookSensivity(0.1f),

			m_Forward(0.0f),
			m_Right(0.0f),
			m_Up(0.0f),

			m_IsFirstMouse(true),
			m_LastMX(0.0f),
			m_LastMY(0.0f)
		{

		}

		void OnInputEvent(CEvent& ev);

		void SetCamera(const std::shared_ptr<CCamera>& camera);

		std::shared_ptr<CCamera>& GetCamera();

		void MoveForward(float forward);
		void MoveRight(float right);
		void MoveUp(float up);

		void Update(float dt);
		void AddRotationAxes(glm::vec3 rawRotAxes);

		float GetForwardSpeed() const { return m_ForwardSpeed; }
		void SetForwardSpeed(float val) { m_ForwardSpeed = val; }
		float GetBackwardSpeed() const { return m_BackwardSpeed; }
		void SetBackwardSpeed(float val) { m_BackwardSpeed = val; }
		float GetSideSpeed() const { return m_SideSpeed; }
		void SetSideSpeed(float val) { m_SideSpeed = val; }
		float GetUpSpeed() const { return m_UpSpeed; }
		void SetUpSpeed(float val) { m_UpSpeed = val; }

	};


}
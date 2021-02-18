#pragma once

#include <ke_pch.h>
#include <KraisEngine.h>


namespace KE {

	class CCamera;

	class CCameraController
	{
	protected:
		float m_ForwardSpeed;
		float m_BackwardSpeed;
		float m_SideSpeed;
		float m_UpSpeed;

		float m_Forward;
		float m_Right;
		float m_Up;

		float m_LookSensivity;

		std::shared_ptr<CCamera> m_Camera;

	public:

		CCameraController();

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
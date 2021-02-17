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

		std::shared_ptr<CCamera> m_Camera;

	public:

		CCameraController();

		void SetCamera(const std::shared_ptr<CCamera>& camera);

		std::shared_ptr<CCamera>& GetCamera();

		void MoveForward(float forward);
		void MoveRight(float right);
		void MoveUp(float up);

		void Update(float dt);
	};


}
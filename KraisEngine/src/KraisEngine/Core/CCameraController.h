#pragma once

#include <ke_pch.h>
#include <KraisEngine.h>

namespace KE {

	class CCameraController
	{
	public:
		float m_ForwardSpeed;
		float m_BackwardSpeed;
		float m_SideSpeed;

		float m_Forward;
		float m_Right;
		float m_Up;

		std::shared_ptr<CCamera> m_Camera;

	public:
		void Update(float dt) {
			if (m_Forward != 0) {
				
			}
		}
	};


}
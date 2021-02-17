#pragma once

#include <ke_pch.h>
#include <KraisEngine.h>

namespace KE {

	enum class ECameraType {
		Orthographic,
		Perspective
	};

	class CCamera
	{
	public:

		CCamera() { }

		ECameraType GetCameraType() const { return m_CameraType; }
		glm::mat4& const GetViewMatrix() { return m_View; };
		glm::mat4& const GetProjectionMatrix() { return m_Projection; };

		/// <summary>
		/// Обновление матриц вида и проекции
		/// </summary>
		void Update() {

			if (m_IsViewObsolete)
				UpdateView();

			UpdateProjection();
		}

		void UpdateView() {
			m_View = glm::lookAt(m_Position, m_Position + m_Forward, m_Up);
			m_IsViewObsolete = false;
			KE_CORE_INFO("<UpdateView>");
		}
		void UpdateView(const glm::vec3& pos, const glm::vec3& tar, const glm::vec3& up) {
			m_Position = pos;
			m_Up = up;
			UpdateView();
		}

		void UpdateProjection() {
			switch (m_CameraType)
			{
			case ECameraType::Orthographic:
				if (m_IsOrhtographicObsolete)
					UpdateOrthographic();
				break;
			case ECameraType::Perspective:
				if (m_IsPerspectiveObsolete)
					UpdatePerspective();
				break;
			default:
				break;
			}
		}

		void UpdatePerspective() {
			m_Projection = glm::perspective(m_PerspectiveFov, m_PerspectiveRatio, m_MinDistance, m_MaxDistance);
			m_CameraType = ECameraType::Perspective;
			m_IsPerspectiveObsolete = false;
			KE_CORE_INFO("<UpdateProjection> PERSPECTIVE");

		}
		void UpdatePerspective(float fov, float ratio, float min, float max) {
			m_PerspectiveFov = fov;
			m_PerspectiveRatio = ratio;
			m_MinDistance = min;
			m_MaxDistance = max;
			UpdatePerspective();
		}

		void UpdateOrthographic() {
			m_Projection = glm::ortho(m_OrthoMinWidth, m_OrthoMaxWidth, m_OrthoMinHeight, m_OrthoMaxHeight, m_MinDistance, m_MaxDistance);
			m_CameraType = ECameraType::Orthographic;
			m_IsOrhtographicObsolete = false;
			KE_CORE_INFO("<UpdateProjection> ORTHOGRAPHIC");
			//m_IsProjectionObsolete = false;
		}
		void UpdateOrthographic(float minw, float maxw, float minh, float maxh, float mind, float maxd) {
			m_OrthoMinWidth = minw;
			m_OrthoMaxWidth = maxw;
			m_OrthoMinHeight = minh;
			m_OrthoMaxHeight = maxh;
			m_MinDistance = mind;
			m_MaxDistance = maxd;
			UpdateOrthographic();
		}

		glm::vec3 const& GetPosition() const { return m_Position; }
		void SetPosition(const glm::vec3& val) { m_IsViewObsolete = true; m_Position = val; }
		void AddPosition(const glm::vec3& val) { SetPosition(m_Position + val); }
		void AddPositionRelative(const glm::vec3& val) { AddPosition(val); }
		//void AddPosition(const glm::vec3& val) { SetPosition(m_Position += val); }

		glm::vec3 const& GetForward() const { return m_Forward; }
		void SetForward(const glm::vec3& val) { m_IsViewObsolete = true; m_Forward = glm::normalize(val); }
		void SetTarget(const glm::vec3& val) { SetForward(val - m_Position); }
		//void SetDirection(const glm::vec3& val) { SetTarget(m_Position + val); }

		/// <summary>
		/// Право относительно камеры. Расчитывается при вызове
		/// </summary>
		/// <returns></returns>
		glm::vec3 GetRight() const {
			return glm::normalize(glm::cross(m_Forward, m_Up));
		}

		glm::vec3 const& GetUp() const { return m_Up; }
		void SetUp(const glm::vec3& val) { m_IsViewObsolete = true; m_Up = val; }


		float GetFov() const { return m_PerspectiveFov; }
		void SetFov(float val) { m_IsPerspectiveObsolete = true; m_PerspectiveFov = val; }

		float GetRatio() const { return m_PerspectiveRatio; }
		void SetRatio(float val) { m_IsPerspectiveObsolete = true; m_PerspectiveRatio = val; }


		float GetOrthoMinWidth() const { return m_OrthoMinWidth; }
		void SetOrthoMinWidth(float val) { m_IsOrhtographicObsolete = true; m_OrthoMinWidth = val; }

		float GetOrthoMaxWidth() const { return m_OrthoMaxWidth; }
		void SetOrthoMaxWidth(float val) { m_IsOrhtographicObsolete = true; m_OrthoMaxWidth = val; }

		float GetOrthoMinHeight() const { return m_OrthoMinHeight; }
		void SetOrthoMinHeight(float val) { m_IsOrhtographicObsolete = true; m_OrthoMinHeight = val; }

		float GetOrthoMaxHeight() const { return m_OrthoMaxHeight; }
		void SetOrthoMaxHeight(float val) { m_IsOrhtographicObsolete = true; m_OrthoMaxHeight = val; }

	protected:

		bool m_IsViewObsolete = true;
		bool m_IsOrhtographicObsolete = true;
		bool m_IsPerspectiveObsolete = true;

		ECameraType m_CameraType;

		glm::vec3 m_Position = glm::vec3(0.0f, 0.0f, 0.0f);
		glm::vec3 m_Forward = glm::vec3(0.0f, 0.0f, -1.0f);;
		glm::vec3 m_Up = glm::vec3(0.0f, 1.0f, 0.0f);

		float m_MinDistance = 0.1f;
		float m_MaxDistance = 100.0f;

		float m_PerspectiveFov = 3.14f / 2.0f;
		float m_PerspectiveRatio = 1;

		float m_OrthoMinWidth = 0.0f;
		float m_OrthoMaxWidth = 800.0f;
		float m_OrthoMinHeight = 0.0f;
		float m_OrthoMaxHeight = 800.0f;

		glm::mat4 m_View;
		glm::mat4 m_Projection;
	};


}

#pragma once
#include "Hazel/Renderer/Camera.h"
namespace Hazel {
	class SceneCamera : public Camera {
	public:
		enum class ProjectionType {
			Perspective = 0,
			Orthographic = 1
		};
	public:
		SceneCamera();
		virtual ~SceneCamera() = default;
		void SetViewPortSize(uint32_t width, uint32_t height);
		inline ProjectionType GetProjectionType() const { return m_ProjectionType; };
		inline void SetProjectionType(ProjectionType type) {
			m_ProjectionType = type; RecalculateProjection();
		};

		void SetOrthographic(float size, float nearClip, float farClip);
		void SetOrthographicSize(float size) { m_OrthographicSize = size; RecalculateProjection(); }
		inline float GetOrthographicSize() const {
			return m_OrthographicSize;
		}
		inline void SetOrthographicNearClip(float nearClip) {
			m_OrthographicNear = nearClip;
			RecalculateProjection();
		}
		inline float GetOrthographicNearClip() const {
			return m_OrthographicNear;
		}
		inline void SetOrthographicFarClip(float farClip) {
			m_OrthographicFar = farClip;
			RecalculateProjection();
		}
		inline float GetOrthographicFarClip() const {
			return m_OrthographicFar;
		}

		void SetPerspective(float FOV, float nearClip, float farClip);
		inline void SetPerspectiveNearClip(float nearClip) {
			m_PerspectiveNear = nearClip;
			RecalculateProjection();
		}
		inline float GetPerspectiveNearClip() const {
			return m_PerspectiveNear;
		}
		inline void SetPerspectiveFarClip(float farClip) {
			m_PerspectiveFar = farClip;
			RecalculateProjection();
		}
		inline float GetPerspectiveFarClip() const {
			return m_PerspectiveFar;
		}
		inline void SetPerspectiveFOV(float FOV) {
			m_PerspectiveFOV = FOV;
			RecalculateProjection();
		}
		inline float GetPerspectiveFOV() const {
			return m_PerspectiveFOV;
		}

	private:
		void RecalculateProjection();
	private:
		ProjectionType m_ProjectionType = ProjectionType::Orthographic;

		float m_OrthographicSize = 10.0f;
		float m_OrthographicNear = -1.0f;
		float m_OrthographicFar = 1.0f;

		float m_PerspectiveFOV = glm::radians(45.0f);
		float m_PerspectiveNear = 0.1f;
		float m_PerspectiveFar = 1000.0f;

		float m_AspectRatio = 0.0f;
	};
}
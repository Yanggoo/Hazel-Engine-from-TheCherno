#pragma once
#include "Hazel.h"
namespace Hazel {
	class EditorLayer : public Layer {
	public:
		EditorLayer(const std::string& name = "EditorLayer");
		virtual ~EditorLayer() = default;
		virtual void OnAttach() override;
		virtual void OnDetach() override;
		virtual void OnUpdate(Timestep ts) override;
		virtual void OnImGuiRender() override;
		virtual void OnEvent(Event& event) override;
	private:
		bool OnKeyPressed(KeyPressedEvent& e);
		void NewScene();
		void OpenScene();
		void SaveSceneAs();
	private:

		//OrthographicCameraController m_CameraController;
		Ref<VertexArray> m_SquareVA;
		Ref<Shader> m_FlatColorShader;
		Ref<FrameBuffer> m_Framebuffer;
		glm::vec2 m_ViewportSize = { 0.0f, 0.0f };
		glm::vec4 m_SquareColor = { 0.2f, 0.3f, 0.8f, 1.0f };
		Ref<Texture2D> m_Texture;
		bool m_ViewPortFocused = false;
		bool m_ViewPortHovered = false;
		Ref<Scene> m_ActiveScene;
		Entity m_SquareEntity;
		Entity m_CameraEntity;
		Entity m_SecondCamera;
		bool m_PrimaryCamera = true;
		SceneHierarchyPanel m_SceneHierarchyPanel;
	};
}
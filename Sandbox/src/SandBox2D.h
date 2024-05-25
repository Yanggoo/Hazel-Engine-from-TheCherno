#pragma once
#include "Hazel.h"
class SandBox2D : public Hazel::Layer {
public:
	SandBox2D(const std::string& name = "SandBox2DLayer");
	virtual ~SandBox2D() = default;
	virtual void OnAttach() override;
	virtual void OnDetach() override;
	virtual void OnUpdate(Hazel::Timestep ts) override;
	virtual void OnImGuiRender() override;
	virtual void OnEvent(Hazel::Event& event) override;
private:

	Hazel::OrthographicCameraController m_CameraController;
	Hazel::Ref<Hazel::VertexArray> m_SquareVA;
	Hazel::Ref<Hazel::Shader> m_FlatColorShader;
	glm::vec4 m_SquareColor = { 0.2f, 0.3f, 0.8f, 1.0f };
	Hazel::Ref<Hazel::Texture2D> m_Texture;
};
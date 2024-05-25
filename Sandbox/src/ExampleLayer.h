#pragma once
#include "Hazel.h"
#include "glm/gtc/matrix_transform.hpp"
#include "imgui/imgui.h"
#include "glm/gtc/type_ptr.hpp"

class ExampleLayer : public Hazel::Layer {
public:
	ExampleLayer();

	void OnImGuiRender() override;
	void OnUpdate(Hazel::Timestep ts) override;
	void OnEvent(Hazel::Event& event) override;

private:
	std::shared_ptr<Hazel::Shader> m_Shader;
	std::shared_ptr<Hazel::VertexArray> m_VertexArray;

	std::shared_ptr<Hazel::Shader> m_FlatColorShader;
	std::shared_ptr<Hazel::VertexArray> m_VertexArraySquare;

	std::shared_ptr<Hazel::VertexArray> m_VertexArrayImage;
	std::shared_ptr<Hazel::Texture2D> m_Texture;
	std::shared_ptr<Hazel::Texture2D> m_ChernoLogoTexture;

	Hazel::ShaderLibrary m_ShaderLibrary;

	Hazel::OrthographicCameraController m_CameraController;
	glm::vec3 m_CameraPosition = glm::vec3(0.0f);
	float m_CameraRotation = 0.0f;
	float m_CameraRotateSpeed = 30.0f;
	float m_CameraMoveSpeed = 2.0f;
	glm::vec3 m_SquareColor = { 0,0,0 };
};
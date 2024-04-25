#include <Hazel.h>
#include "hzpch.h"
#include "ImGui/imgui.h"

class ExampleLayer : public Hazel::Layer {
public:
	ExampleLayer() :Layer("Example"), m_Camera(-1.6f, 1.6f, -0.9f, 0.9f) {
		{
			m_VertexArray.reset(Hazel::VertexArray::Create());

			float vertices[3 * 7] = {
				-0.5f, -0.5f, 0.0f, 0.8f, 0.2f, 0.8f, 1.0f,
				 0.5f, -0.5f, 0.0f, 0.2f, 0.3f, 0.8f, 1.0f,
				 0.0f,  0.5f, 0.0f, 0.8f, 0.8f, 0.2f, 1.0f
			};
			std::shared_ptr<Hazel::VertexBuffer> vertexBuffer;
			vertexBuffer.reset(Hazel::VertexBuffer::Create(vertices, sizeof(vertices)));
			{
				Hazel::BufferLayeout layout = {
					{Hazel::ShaderDataType::Float3,"a_Position",true},
					{Hazel::ShaderDataType::Float4,"a_Color",true},
				};
				vertexBuffer->SetBufferLayout(layout);
			}
			m_VertexArray->AddVertexBuffer(vertexBuffer);

			uint32_t indices[3] = { 0,1,2 };
			std::shared_ptr<Hazel::IndexBuffer> indexBuffer;
			indexBuffer.reset(Hazel::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));
			m_VertexArray->SetIndexBuffer(indexBuffer);

			const std::string vertexSrc = R"(
					#version 330 core
					
					layout(location = 0) in vec3 a_Position;
					layout(location = 1) in vec4 a_Color;
					uniform mat4 u_ViewProjection;
					out vec3 v_Position;
					out vec4 v_Color;
					void main()
					{
						v_Position = a_Position;
						v_Color = a_Color;
						gl_Position = u_ViewProjection * vec4(a_Position, 1.0);	
					}
				)";

			const std::string fragmentSrc = R"(
					#version 330 core
					
					layout(location = 0) out vec4 color;
					in vec3 v_Position;
					in vec4 v_Color;
					void main()
					{
						color = vec4(v_Position * 0.5 + 0.5, 1.0);
						color = v_Color;
					}
				)";

			m_Shader.reset(new Hazel::Shader(vertexSrc, fragmentSrc));
		}

		//Draw a square
		{
			m_VertexArraySquare.reset(Hazel::VertexArray::Create());

			float vertices[3 * 4] = {
				-0.75f, -0.75f, 0.0f,
				 0.75f, -0.75f, 0.0f,
				 0.75f,  0.75f, 0.0f,
				 -0.75f,  0.75f, 0.0f,
			};
			std::shared_ptr<Hazel::VertexBuffer> vertexBuffer;
			vertexBuffer.reset(Hazel::VertexBuffer::Create(vertices, sizeof(vertices)));
			{
				Hazel::BufferLayeout layout = {
					{Hazel::ShaderDataType::Float3,"a_Position",true},
				};
				vertexBuffer->SetBufferLayout(layout);
			}
			m_VertexArraySquare->AddVertexBuffer(vertexBuffer);

			uint32_t indices[6] = { 0,1,2,2,3,0 };
			std::shared_ptr<Hazel::IndexBuffer> indexBuffer;
			indexBuffer.reset(Hazel::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));
			m_VertexArraySquare->SetIndexBuffer(indexBuffer);

			const std::string vertexSrc = R"(
					#version 330 core
					
					layout(location = 0) in vec3 a_Position;
					uniform mat4 u_ViewProjection;
					out vec3 v_Position;
					void main()
					{
						v_Position = a_Position;
						gl_Position = u_ViewProjection * vec4(a_Position, 1.0);	
					}
				)";

			const std::string fragmentSrc = R"(
					#version 330 core
					
					layout(location = 0) out vec4 color;
					in vec3 v_Position;
					void main()
					{
						color = vec4(v_Position * 0.5 + 0.5, 1.0);
						color = vec4(0.2f, 0.3f, 0.8f, 1.0f);
					}
				)";

			m_BlueShader.reset(new Hazel::Shader(vertexSrc, fragmentSrc));
		}
	}
	void OnUpdate() override {
		m_CameraPosition = m_Camera.GetPosition();
		if (Hazel::Input::IsKeyPressed(HZ_KEY_LEFT)) {
			m_CameraPosition.x -= m_CameraMoveSpeed;
		}
		else if (Hazel::Input::IsKeyPressed(HZ_KEY_RIGHT)) {
			m_CameraPosition.x += m_CameraMoveSpeed;
		}
		if (Hazel::Input::IsKeyPressed(HZ_KEY_UP)) {
			m_CameraPosition.y += m_CameraMoveSpeed;
		}
		else if (Hazel::Input::IsKeyPressed(HZ_KEY_DOWN)) {
			m_CameraPosition.y -= m_CameraMoveSpeed;
		}
		m_CameraRotation = m_Camera.GetRotation();
		if (Hazel::Input::IsKeyPressed(HZ_KEY_Q)) {
			m_CameraRotation -= m_CameraRotateSpeed;
		}
		else if (Hazel::Input::IsKeyPressed(HZ_KEY_E)) {
			m_CameraRotation += m_CameraRotateSpeed;
		}

		m_Camera.SetPosition(m_CameraPosition);
		m_Camera.SetRotation(m_CameraRotation);
		Hazel::RenderCommand::SetClearColor({ 0.2f, 0.2f, 0.2f, 1 });
		Hazel::RenderCommand::Clear();
		Hazel::Renderer::Begin(m_Camera);
		Hazel::Renderer::Submit(m_BlueShader, m_VertexArraySquare);
		Hazel::Renderer::Submit(m_Shader, m_VertexArray);
		Hazel::Renderer::End();
	}
	void OnEvent(Hazel::Event& event) override {
	}

	virtual void OnImGuiRender() override {
		ImGui::Begin("Test");
		ImGui::Text("Hello World");
		ImGui::End();
	}
private:
	std::shared_ptr<Hazel::Shader> m_Shader;
	std::shared_ptr<Hazel::VertexArray> m_VertexArray;

	std::shared_ptr<Hazel::Shader> m_BlueShader;
	std::shared_ptr<Hazel::VertexArray> m_VertexArraySquare;
	Hazel::OrthographicCamera m_Camera;
	glm::vec3 m_CameraPosition = glm::vec3(0.0f);
	float m_CameraRotation = 0.0f;
	float m_CameraRotateSpeed = 2.0f;
	float m_CameraMoveSpeed = 0.1f;
};

class Sandbox : public Hazel::Application {
public:
	Sandbox() {
		PushLayer(new ExampleLayer());
	}
	~Sandbox() {

	}
private:
};

Hazel::Application* Hazel::CreateApplication() {
	return new Sandbox();
}

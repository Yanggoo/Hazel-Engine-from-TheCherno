#include "hzpch.h"
#include "ExampleLayer.h"
ExampleLayer::ExampleLayer() :Hazel::Layer("Example"), m_CameraController((float)(1280.0 / 720), true) {
	{
		m_VertexArray = Hazel::VertexArray::Create();

		float vertices[3 * 7] = {
			-0.5f, -0.5f, 0.0f, 0.8f, 0.2f, 0.8f, 1.0f,
			 0.5f, -0.5f, 0.0f, 0.2f, 0.3f, 0.8f, 1.0f,
			 0.0f,  0.5f, 0.0f, 0.8f, 0.8f, 0.2f, 1.0f
		};
		Hazel::Ref<Hazel::VertexBuffer> vertexBuffer(Hazel::VertexBuffer::Create(vertices, sizeof(vertices)));
		{
			Hazel::BufferLayeout layout = {
				{Hazel::ShaderDataType::Float3,"a_Position",true},
				{Hazel::ShaderDataType::Float4,"a_Color",true},
			};
			vertexBuffer->SetBufferLayout(layout);
		}
		m_VertexArray->AddVertexBuffer(vertexBuffer);

		uint32_t indices[3] = { 0,1,2 };
		Hazel::Ref<Hazel::IndexBuffer> indexBuffer;
		indexBuffer = Hazel::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t));
		m_VertexArray->SetIndexBuffer(indexBuffer);

		const std::string vertexSrc = R"(
					#version 330 core
					
					layout(location = 0) in vec3 a_Position;
					layout(location = 1) in vec4 a_Color;
					uniform mat4 u_ViewProjection;
					uniform mat4 u_Transform;
					out vec3 v_Position;
					out vec4 v_Color;
					void main()
					{
						v_Position = a_Position;
						v_Color = a_Color;
						gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);	
					}
				)";

		const std::string fragmentSrc = R"(
					#version 330 core
					
					layout(location = 0) out vec4 color;
					in vec3 v_Position;
					in vec4 v_Color;
					void main()
					{
						color = v_Color;
					}
				)";

		m_Shader = Hazel::Shader::Create("specific", vertexSrc, fragmentSrc);
	}

	//Draw a square
	{
		m_VertexArraySquare = Hazel::VertexArray::Create();

		float vertices[3 * 4] = {
			-0.5f, -0.5f, 0.0f,
			 0.5f, -0.5f, 0.0f,
			 0.5f,  0.5f, 0.0f,
			-0.5f,  0.5f, 0.0f,
		};
		Hazel::Ref<Hazel::VertexBuffer> vertexBuffer(Hazel::VertexBuffer::Create(vertices, sizeof(vertices)));
		{
			Hazel::BufferLayeout layout = {
				{Hazel::ShaderDataType::Float3,"a_Position",true},
			};
			vertexBuffer->SetBufferLayout(layout);
		}
		m_VertexArraySquare->AddVertexBuffer(vertexBuffer);

		uint32_t indices[6] = { 0,1,2,2,3,0 };
		Hazel::Ref<Hazel::IndexBuffer> indexBuffer;
		indexBuffer = Hazel::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t));
		m_VertexArraySquare->SetIndexBuffer(indexBuffer);

		const std::string vertexSrc = R"(
					#version 330 core
					
					layout(location = 0) in vec3 a_Position;
					uniform mat4 u_ViewProjection;
					uniform mat4 u_Transform;
					out vec3 v_Position;
					void main()
					{
						v_Position = a_Position;
						gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);	
					}
				)";

		const std::string fragmentSrc = R"(
					#version 330 core
					
					layout(location = 0) out vec4 color;
					uniform vec3 u_Color;
					in vec3 v_Position;
					void main()
					{
						color = vec4(u_Color,1.0);
					}
				)";

		m_FlatColorShader = Hazel::Shader::Create("flat", vertexSrc, fragmentSrc);
	}

	//Draw a picture
	{
		m_VertexArrayImage = Hazel::VertexArray::Create();

		float vertices[5 * 4] = {
			-0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
			 0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
			 0.5f,  0.5f, 0.0f, 1.0f, 1.0f,
			-0.5f,  0.5f, 0.0f, 0.0f, 1.0f
		};
		Hazel::Ref<Hazel::VertexBuffer> vertexBuffer(Hazel::VertexBuffer::Create(vertices, sizeof(vertices)));
		{
			Hazel::BufferLayeout layout = {
				{Hazel::ShaderDataType::Float3,"a_Position"},
				{Hazel::ShaderDataType::Float2,"a_TextureCoord"},
			};
			vertexBuffer->SetBufferLayout(layout);
		}
		m_VertexArrayImage->AddVertexBuffer(vertexBuffer);

		uint32_t indices[6] = { 0,1,2,2,3,0 };
		Hazel::Ref<Hazel::IndexBuffer> indexBuffer;
		indexBuffer = Hazel::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t));
		m_VertexArrayImage->SetIndexBuffer(indexBuffer);

		auto m_TextureShader = m_ShaderLibrary.Load("assets/shaders/Texture.glsl");
		m_TextureShader->SetInt("u_Texture", 0);
		m_Texture = Hazel::Texture2D::Create("assets/textures/Checkerboard.png");

		m_ChernoLogoTexture = Hazel::Texture2D::Create("assets/textures/ChernoLogo.png");
	}


}

void ExampleLayer::OnImGuiRender() {
	ImGui::Begin("Settings!");
	ImGui::ColorEdit3("Square Color", glm::value_ptr(m_SquareColor));
	ImGui::End();
}

void ExampleLayer::OnUpdate(Hazel::Timestep ts) {
	m_CameraController.OnUpdate(ts);

	Hazel::RenderCommand::SetClearColor({ 0.2f, 0.2f, 0.2f, 1 });
	Hazel::RenderCommand::Clear();
	Hazel::Renderer::BeginScene(m_CameraController.GetCamera());
	glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(0.1f, 0.1f, 1.0f));

	m_FlatColorShader->Bind();
	m_FlatColorShader->SetFloat3("u_Color", m_SquareColor);
	for (int i = 0; i < 20; i++)
		for (int j = 0; j < 20; j++) {
			glm::vec3 pos = glm::vec3(0.11f * i, 0.11f * j, 0.0f);
			Hazel::Renderer::Submit(m_FlatColorShader, m_VertexArraySquare, glm::translate(glm::mat4(1.0f), pos) * scale);
		}
	//Hazel::Renderer::Submit(m_FlatColorShader, m_VertexArraySquare);
	//Hazel::Renderer::Submit(m_Shader, m_VertexArray);
	m_Texture->Bind(0);
	auto m_TextureShader = m_ShaderLibrary.Get("Texture");
	Hazel::Renderer::Submit(m_TextureShader, m_VertexArrayImage);
	m_ChernoLogoTexture->Bind(0);
	Hazel::Renderer::Submit(m_TextureShader, m_VertexArrayImage);
	Hazel::Renderer::EndScene();
}

void ExampleLayer::OnEvent(Hazel::Event& event) {
	m_CameraController.OnEvent(event);
}
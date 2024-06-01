#include "hzpch.h"
#include "Renderer2D.h"
#include "VertexArray.h"
#include "Shader.h"
#include "RenderCommand.h"
#include "Buffer.h"
#include <glm/gtc/matrix_transform.hpp>
namespace Hazel {
	struct QuadVertex {
		glm::vec3 Position;
		glm::vec4 Color;
		glm::vec2 TexCoord;
		float TexIndex;
		float TilingFactor;

	};

	struct Renderer2DData {
		static const uint32_t MaxQuads = 1000;
		static const uint32_t MaxQuadVertices = MaxQuads * 4;
		static const uint32_t MaxQuadIndices = MaxQuads * 6;
		static const uint32_t MaxTextureSlots = 32;

		Ref<VertexArray> QuadVertexArray;
		Ref<VertexBuffer> QuadVertexBuffer;
		Ref<Shader> TextureShader;
		Ref<Texture2D> WhiteTexture;
		QuadVertex* QuadVertexBufferBase = nullptr;
		QuadVertex* QuadVertexBufferPtr = nullptr;
		uint32_t QuadIndexCount = 0;

		std::array<Ref<Texture2D>, MaxTextureSlots> TextureSlots;
		uint32_t TextureSlotIndex = 1;

		glm::vec4 QuadVertexPositions[4];

		Renderer2D::Statistics Stats;
	};

	static Renderer2DData s_Data;

	void Renderer2D::Init()
	{
		HZ_PROFILE_FUNCTION();

		s_Data.QuadVertexArray = VertexArray::Create();

		s_Data.QuadVertexBuffer = VertexBuffer::Create(Renderer2DData::MaxQuadVertices * sizeof(QuadVertex));
		BufferLayeout layout{
			{ShaderDataType::Float3,"a_Position",false},
			{ShaderDataType::Float4,"a_Color",false},
			{ShaderDataType::Float2,"a_TextureCoord",false},
			{ShaderDataType::Float,"a_TexIndex",false},
			{ShaderDataType::Float,"a_TilingFactor",false},
		};
		s_Data.QuadVertexBuffer->SetBufferLayout(layout);

		s_Data.QuadVertexArray->AddVertexBuffer(s_Data.QuadVertexBuffer);

		s_Data.QuadVertexBufferBase = new QuadVertex[Renderer2DData::MaxQuadVertices];

		uint32_t* indices = new uint32_t[Renderer2DData::MaxQuadIndices];
		uint32_t offset = 0;
		for (uint32_t i = 0; i < Renderer2DData::MaxQuadIndices;) {
			indices[i + 0] = offset;
			indices[i + 1] = offset + 1;
			indices[i + 2] = offset + 2;

			indices[i + 3] = offset + 2;
			indices[i + 4] = offset + 3;
			indices[i + 5] = offset + 0;
			i += 6;
			offset += 4;
		}
		auto indexBuffer = IndexBuffer::Create(indices, Renderer2DData::MaxQuadIndices);
		s_Data.QuadVertexArray->SetIndexBuffer(indexBuffer);
		delete[] indices;

		s_Data.TextureShader = Shader::Create("assets/shaders/Texture.glsl");

		s_Data.WhiteTexture = Texture2D::Create(1, 1);
		uint32_t whiteTextureData = 0xffffffff;
		s_Data.WhiteTexture->SetData(&whiteTextureData, sizeof(uint32_t));

		int samplers[Renderer2DData::MaxTextureSlots];
		for (int i = 0; i < Renderer2DData::MaxTextureSlots; i++)
			samplers[i] = i;

		s_Data.TextureShader->Bind();
		s_Data.TextureShader->SetIntArray("u_Textures", samplers, Renderer2DData::MaxTextureSlots);
		s_Data.TextureSlots[0] = s_Data.WhiteTexture;

		s_Data.QuadVertexPositions[0] = { -0.5f, -0.5f, 0.0f, 1.0f };
		s_Data.QuadVertexPositions[1] = { 0.5f, -0.5f, 0.0f, 1.0f };
		s_Data.QuadVertexPositions[2] = { 0.5f,  0.5f, 0.0f, 1.0f };
		s_Data.QuadVertexPositions[3] = { -0.5f,  0.5f, 0.0f, 1.0f };
	}

	void Renderer2D::ShutDown()
	{
		HZ_PROFILE_FUNCTION();
		delete[] s_Data.QuadVertexBufferBase;
	}

	void Renderer2D::BeginScene(const OrthographicCamera& camera)
	{
		HZ_PROFILE_FUNCTION();

		s_Data.TextureShader->Bind();
		s_Data.TextureShader->SetMat4("u_ViewProjection", camera.GetViewProjectionMatrix());
		StartBatch();
	}

	void Renderer2D::BeginScene(const Camera& camera, const glm::mat4& transform)
	{
		HZ_PROFILE_FUNCTION();

		glm::mat4 viewProjection = camera.GetProjection() * glm::inverse(transform);

		s_Data.TextureShader->Bind();
		s_Data.TextureShader->SetMat4("u_ViewProjection", viewProjection);
		StartBatch();
	}

	void Renderer2D::BeginScene(const EditorCamera& camera)
	{
		HZ_PROFILE_FUNCTION();
		glm::mat4 viewProjection = camera.GetViewProjection();

		s_Data.TextureShader->Bind();
		s_Data.TextureShader->SetMat4("u_ViewProjection", viewProjection);
		StartBatch();
	}

	void Renderer2D::EndScene()
	{
		HZ_PROFILE_FUNCTION();
		s_Data.QuadVertexArray->Bind();
		uint32_t size = (uint32_t)((uint8_t*)s_Data.QuadVertexBufferPtr - (uint8_t*)s_Data.QuadVertexBufferBase);
		s_Data.QuadVertexBuffer->SetData(s_Data.QuadVertexBufferBase, size);

		Flush();

	}

	void Renderer2D::Flush() {
		HZ_PROFILE_FUNCTION();
		if (s_Data.QuadIndexCount == 0)
			return; // Nothing to draw

		s_Data.QuadVertexArray->Bind();
		uint32_t size = (uint32_t)((uint8_t*)s_Data.QuadVertexBufferPtr - (uint8_t*)s_Data.QuadVertexBufferBase);
		s_Data.QuadVertexBuffer->SetData(s_Data.QuadVertexBufferBase, size);

		for (uint32_t i = 0; i < s_Data.TextureSlotIndex; i++)
		{
			s_Data.TextureSlots[i]->Bind(i);
		}
		RenderCommand::DrawIndexed(s_Data.QuadVertexArray, s_Data.QuadIndexCount);
		s_Data.Stats.DrawCalls++;
	}

	void Renderer2D::DrawQuad(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color)
	{
		DrawQuad(glm::vec3(position, 0.0f), size, color);
	}

	void Renderer2D::DrawQuad(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color)
	{
		HZ_PROFILE_FUNCTION();
		glm::mat4 transform = glm::translate(glm::mat4(1.0f), position) * glm::scale(glm::mat4(1.0f), glm::vec3(size, 0.0f));
		DrawQuad(transform, color);

	}

	void Renderer2D::DrawQuad(const glm::vec2& position, const glm::vec2& size, const Ref<Texture2D>& texture, float tilingFactor /*= 1.0f*/, const glm::vec4& tintColor /*= glm::vec4(1.0f)*/)
	{
		DrawQuad(glm::vec3(position, 0), size, texture, tilingFactor, tintColor);
	}

	void Renderer2D::DrawQuad(const glm::vec3& position, const glm::vec2& size, const Ref<Texture2D>& texture, float tilingFactor /*= 1.0f*/, const glm::vec4& tintColor /*= glm::vec4(1.0f)*/)
	{
		HZ_PROFILE_FUNCTION();
		glm::mat4 transform = glm::translate(glm::mat4(1.0f), position)
			* glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });
		DrawQuad(transform, texture,tilingFactor,tintColor);
	}

	void Renderer2D::DrawQuad(const glm::mat4& transform, const glm::vec4& color) {
		HZ_PROFILE_FUNCTION();
		constexpr size_t quadVertexCount = 4;
		constexpr float textureIndex = 0.0f;//white texture
		constexpr glm::vec2 textureCoords[] = { {0.0f,0.0f},{1.0f,0.0f},{1.0f,1.0f},{0.0f,1.0f} };
		constexpr float tilingFactor = 1.0f;
		if (s_Data.Stats.QuadCount >= Renderer2DData::MaxQuads) {
			NextBatch();
		}
		for (size_t i = 0; i < quadVertexCount; i++) {
			s_Data.QuadVertexBufferPtr->Position = transform * s_Data.QuadVertexPositions[i];
			s_Data.QuadVertexBufferPtr->Color = color;
			s_Data.QuadVertexBufferPtr->TexCoord = textureCoords[i];
			s_Data.QuadVertexBufferPtr->TexIndex = textureIndex;
			s_Data.QuadVertexBufferPtr->TilingFactor = tilingFactor;
			s_Data.QuadVertexBufferPtr++;
		}
		s_Data.QuadIndexCount += 6;
		s_Data.Stats.QuadCount++;
	}
	void Renderer2D::DrawQuad(const glm::mat4& transform, const Ref<Texture2D>& texture, float tilingFactor, const glm::vec4& tintColor) {
		HZ_PROFILE_FUNCTION();

		if (s_Data.Stats.QuadCount >= Renderer2DData::MaxQuads) {
			NextBatch();
		}

		float texIndex = 0.0f;

		for (uint32_t i = 1; i < s_Data.TextureSlotIndex; i++) {
			if (*s_Data.TextureSlots[i] == *texture)
			{
				texIndex = (float)i;
				break;
			}
		}
		if (texIndex == 0.0f) {
			if (s_Data.TextureSlotIndex >= Renderer2DData::MaxTextureSlots) {
				NextBatch();
			}
			s_Data.TextureSlots[s_Data.TextureSlotIndex] = texture;
			texIndex = (float)s_Data.TextureSlotIndex;
			s_Data.TextureSlotIndex++;
		}
		constexpr size_t quadVertexCount = 4;
		constexpr glm::vec2 textureCoords[] = { {0.0f,0.0f},{1.0f,0.0f},{1.0f,1.0f},{0.0f,1.0f} };
		if (s_Data.Stats.QuadCount >= Renderer2DData::MaxQuads) {
			NextBatch();
		}
		for (size_t i = 0; i < quadVertexCount; i++) {
			s_Data.QuadVertexBufferPtr->Position = transform * s_Data.QuadVertexPositions[i];
			s_Data.QuadVertexBufferPtr->Color = tintColor;
			s_Data.QuadVertexBufferPtr->TexCoord = textureCoords[i];
			s_Data.QuadVertexBufferPtr->TexIndex = texIndex;
			s_Data.QuadVertexBufferPtr->TilingFactor = tilingFactor;
			s_Data.QuadVertexBufferPtr++;
		}
		s_Data.QuadIndexCount += 6;
		s_Data.Stats.QuadCount++;
	}

	void Renderer2D::DrawRotatedQuad(const glm::vec2& position, const glm::vec2& size, float rotation, const glm::vec4& color)
	{
		DrawRotatedQuad(glm::vec3(position, 0), size, rotation, color);
	}

	void Renderer2D::DrawRotatedQuad(const glm::vec3& position, const glm::vec2& size, float rotation, const glm::vec4& color)
	{
		HZ_PROFILE_FUNCTION();
		glm::mat4 transform = glm::translate(glm::mat4(1.0f), position) *
			glm::scale(glm::mat4(1.0f), { size, 0.0f }) *
			glm::rotate(glm::mat4(1.0f), glm::radians(rotation), { 0.0f,0.0f,1.0f });

	}

	void Renderer2D::DrawRotatedQuad(const glm::vec2& position, const glm::vec2& size, float rotation, const Ref<Texture2D>& texture, float tilingFactor /*= 1.0f*/, const glm::vec4& tintColor /*= glm::vec4(1.0f)*/)
	{
		DrawRotatedQuad(glm::vec3(position, 0), size, rotation, texture, tilingFactor, tintColor);
	}

	void Renderer2D::DrawRotatedQuad(const glm::vec3& position, const glm::vec2& size, float rotation, const Ref<Texture2D>& texture, float tilingFactor /*= 1.0f*/, const glm::vec4& tintColor /*= glm::vec4(1.0f)*/)
	{
		HZ_PROFILE_FUNCTION();
		glm::mat4 transform = glm::translate(glm::mat4(1.0f), position)
			* glm::rotate(glm::mat4(1.0f), glm::radians(rotation), { 0.0f,0.0f,1.0f })
			* glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });
		DrawQuad(transform, texture, tilingFactor, tintColor);
	}

	void Renderer2D::ResetStats()
	{
		memset(&s_Data.Stats, 0, sizeof(s_Data.Stats));
	}

	Hazel::Renderer2D::Statistics Renderer2D::GetStats()
	{
		return s_Data.Stats;
	}

	void Renderer2D::StartBatch()
	{
		s_Data.QuadVertexBufferPtr = s_Data.QuadVertexBufferBase;
		s_Data.QuadIndexCount = 0;
		s_Data.TextureSlotIndex = 1;
	}

	void Renderer2D::NextBatch()
	{
		HZ_PROFILE_FUNCTION();
		Flush();
		StartBatch();
	}


}
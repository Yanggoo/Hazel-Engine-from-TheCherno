#pragma once
#include "Hazel/Renderer/VertexArray.h"
namespace Hazel {
	class OpenGLVertexArray :public VertexArray
	{
	public:
		OpenGLVertexArray();
		virtual ~OpenGLVertexArray();
		virtual void AddVertexBuffer(Ref<VertexBuffer>& VertexBuffer) override;
		virtual void SetIndexBuffer(Ref<IndexBuffer>& IndexBuffer) override;
		virtual void Bind() const override;
		virtual void UnBind() const override;
		inline virtual const std::vector<Ref<VertexBuffer>> GetVertexBuffers() const override { return m_VertexBuffers; };
		inline virtual const Ref<IndexBuffer> GetIndexBUffer() const override { return m_IndexBuffer; };
	private:
		uint32_t m_RenderID;
		std::vector<Ref<VertexBuffer>> m_VertexBuffers;
		Ref<IndexBuffer> m_IndexBuffer;
	};
}


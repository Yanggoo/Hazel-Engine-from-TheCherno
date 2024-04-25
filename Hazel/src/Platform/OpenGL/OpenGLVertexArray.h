#pragma once
#include "Hazel/Renderer/VertexArray.h"
namespace Hazel {
	class OpenGLVertexArray :public VertexArray
	{
	public:
		OpenGLVertexArray();
		virtual ~OpenGLVertexArray();
		virtual void AddVertexBuffer(std::shared_ptr<VertexBuffer>& VertexBuffer) override;
		virtual void SetIndexBuffer(std::shared_ptr<IndexBuffer>& IndexBuffer) override;
		virtual void Bind() const override;
		virtual void UnBind() const override;
		inline virtual const std::vector<std::shared_ptr<VertexBuffer>> GetVertexBuffers() const override { return m_VertexBuffers; };
		inline virtual const std::shared_ptr<IndexBuffer> GetIndexBUffer() const override { return m_IndexBuffer; };
	private:
		uint32_t m_RenderID;
		std::vector<std::shared_ptr<VertexBuffer>> m_VertexBuffers;
		std::shared_ptr<IndexBuffer> m_IndexBuffer;
	};
}


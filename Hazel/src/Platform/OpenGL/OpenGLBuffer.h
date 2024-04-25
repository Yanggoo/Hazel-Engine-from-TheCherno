#pragma once
#include "Hazel/Renderer/Buffer.h"
namespace Hazel {
	class OpenGLVertexBuffer : public VertexBuffer
	{
	public:
		OpenGLVertexBuffer(float* vertices, uint32_t size);
		virtual ~OpenGLVertexBuffer() override;
		virtual void Bind() const override;
		virtual void UnBind() const override;
		inline virtual const BufferLayeout& GetLayout()const override { return m_Layout; };
		inline virtual void SetBufferLayout(BufferLayeout& layout) override { m_Layout = layout; };
	private:
		uint32_t m_RenderID;
		BufferLayeout m_Layout;
	};

	class OpenGLIndexBuffer : public IndexBuffer
	{
	public:
		OpenGLIndexBuffer(uint32_t* indices, uint32_t count);
		virtual ~OpenGLIndexBuffer() override;
		virtual void Bind() const override;
		virtual void UnBind() const override;
		virtual inline uint32_t GetCount() const override { return m_Count; };
	private:
		uint32_t m_RenderID;
		uint32_t m_Count;
	};
}
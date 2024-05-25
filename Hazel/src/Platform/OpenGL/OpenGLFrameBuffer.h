#pragma once
#include "Hazel/Renderer/FrameBuffer.h"
namespace Hazel {
	class  OpenGLFrameBuffer : public FrameBuffer
	{
	public:
		OpenGLFrameBuffer(const FrameBufferSpecification& spec);
		virtual ~OpenGLFrameBuffer();
		virtual void Bind() override;
		virtual void UnBind() override;
		inline virtual const FrameBufferSpecification& GetSpecification() const override { return m_Specification; };
		virtual uint32_t GetColorAttachmentRendererID() const override { return m_ColorAttachment; };
		virtual void Resize(uint32_t width, uint32_t height) override;
	private:
		void Invalidate();
	private:
		uint32_t m_RendererID = 0;
		uint32_t m_ColorAttachment = 0;
		uint32_t m_DepthAttachment = 0;
		FrameBufferSpecification m_Specification;
	};

}
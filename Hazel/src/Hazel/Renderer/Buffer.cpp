#pragma once
#include "Buffer.h"
#include "hzpch.h"
#include "Renderer.h"
#include "Platform/OpenGL/OpenGLBuffer.h"
#include "RendererAPI.h"
namespace Hazel {

	Hazel::VertexBuffer* VertexBuffer::Create(float* vertices, uint32_t size)
	{
		switch (Renderer::GetAPI()) {
		case RendererAPI::API::None:
			HZ_CORE_ASSERT(false, "RenderAPI::None is not available!");
			return nullptr;
		case RendererAPI::API::OpenGL:
			return new OpenGLVertexBuffer(vertices, size);
		}
		HZ_CORE_ASSERT(false, "RenderAPI::Unkown is not available!");
		return nullptr;
	}

	Hazel::IndexBuffer* IndexBuffer::Create(uint32_t* indices, uint32_t count)
	{
		switch (Renderer::GetAPI()) {
		case RendererAPI::API::None:
			HZ_CORE_ASSERT(false, "RenderAPI::None is not available!");
			return nullptr;
		case RendererAPI::API::OpenGL:
			return new OpenGLIndexBuffer(indices, count);
		}
		HZ_CORE_ASSERT(false, "RenderAPI::Unkown is not available!");
		return nullptr;
	}

}
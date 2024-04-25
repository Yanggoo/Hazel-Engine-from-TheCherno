#pragma once
#include "VertexArray.h"
#include "hzpch.h"
#include "Platform/OpenGL/OpenGLVertexArray.h"
#include "Hazel/Renderer/Renderer.h"
#include "Hazel/Renderer/RendererAPI.h"
namespace Hazel {
	VertexArray* VertexArray::Create()
	{
		switch (Renderer::GetAPI()) {
		case RendererAPI::API::None:
			HZ_CORE_ASSERT(false, "RenderAPI::None is not available!");
			return nullptr;
		case RendererAPI::API::OpenGL:
			return new OpenGLVertexArray();
		}
		HZ_CORE_ASSERT(false, "RenderAPI::Unkown is not available!");
		return nullptr;
	}
}
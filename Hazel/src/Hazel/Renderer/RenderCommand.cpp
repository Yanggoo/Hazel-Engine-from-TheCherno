#include "hzpch.h"
#include"RenderCommand.h"
#include "Platform/OpenGL/OpenGLRendererAPI.h"
namespace Hazel {
	Scope<RendererAPI> RenderCommand::s_RendererAPI = CreateScope <OpenGLRendererAPI>();

	void RenderCommand::init()
	{
		HZ_PROFILE_FUNCTION();

		s_RendererAPI->Init();
	}

	void RenderCommand::SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height)
	{
		s_RendererAPI->SetViewport(x, y, width, height);
	}
}
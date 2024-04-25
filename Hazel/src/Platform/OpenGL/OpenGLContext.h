#pragma once
#include "Hazel/Renderer/GraphicContext.h"
#include "GLFW/glfw3.h"
namespace Hazel {
	class OpenGLContext : public GraphicContext
	{
	public:
		OpenGLContext(GLFWwindow* WindowHandle);
		virtual void Init() override;
		virtual void SwapBuffer() override;
	private:
		GLFWwindow* m_WindowHandle;
	};
}


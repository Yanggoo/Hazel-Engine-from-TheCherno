#include "hzpch.h"
#include "OpenGLContext.h"
#include "Glad/glad.h"

namespace Hazel {

	OpenGLContext::OpenGLContext(GLFWwindow* WindowHandle) :m_WindowHandle(WindowHandle)
	{
		HZ_CORE_ASSERT(WindowHandle, "WindowHandle is null!");
	}

	void OpenGLContext::Init()
	{
		glfwMakeContextCurrent(m_WindowHandle);
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		HZ_CORE_ASSERT(status, "Failed to initialize Glad!");

	}

	void OpenGLContext::SwapBuffer()
	{
		glfwSwapBuffers(m_WindowHandle);
	}

}
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
		HZ_PROFILE_FUNCTION();

		glfwMakeContextCurrent(m_WindowHandle);
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		HZ_CORE_ASSERT(status, "Failed to initialize Glad!");

		HZ_CORE_INFO("OpenGL Info:");
		const char* vendor = reinterpret_cast<const char*>(glGetString(GL_VENDOR));
		std::string vendorString(vendor);
		HZ_CORE_INFO("  Vendor: {0}", vendorString);

		const char* renderer = reinterpret_cast<const char*>(glGetString(GL_RENDERER));
		std::string rendererString(renderer);
		HZ_CORE_INFO("  Renderer: {0}", rendererString);

		const char* version = reinterpret_cast<const char*>(glGetString(GL_VERSION));
		std::string versionString(version);
		HZ_CORE_INFO("  Version: {0}", versionString);

		HZ_CORE_ASSERT(GLVersion.major > 4 || (GLVersion.major == 4 && GLVersion.minor >= 5), "Hazel requires at least OpenGL version 4.5!");

	}

	void OpenGLContext::SwapBuffer()
	{
		HZ_PROFILE_FUNCTION();

		glfwSwapBuffers(m_WindowHandle);
	}

}
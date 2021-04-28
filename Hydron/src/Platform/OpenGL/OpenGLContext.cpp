#include "pch.h"

#include "OpenGLContext.h"

#include <GLFW/glfw3.h>
#include <glad/glad.h>

namespace Hydron {

	OpenGLContext::OpenGLContext(GLFWwindow* windowHandle)
		: m_WindowHandle(windowHandle)
	{
		HYDRON_CORE_ASSERT(windowHandle, "WindowHandle is null!")
	}

	void OpenGLContext::Init()
	{

		glfwMakeContextCurrent(m_WindowHandle);

		// Glad
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		HYDRON_CORE_ASSERT(status, "Failed to initialize Glad!")

	}

	void OpenGLContext::SwapBuffers()
	{
		glfwSwapBuffers(m_WindowHandle);
	}
}
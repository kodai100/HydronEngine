#pragma once


#include "Hydron/Renderer/GraphicsContext.h"

struct GLFWwindow;

namespace Hydron {

	class OpenGLContext : public GraphicsContext
	{
	public:
		OpenGLContext(GLFWwindow* windowHandle);

		virtual void Init() override;
		virtual void SwapBuffers() override;

	private:
		GLFWwindow* m_WindowHandle;
	};

}
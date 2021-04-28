#include "pch.h"
#include "VertexArray.h"

#include "Renderer.h"

#include "Platform/OpenGL/OpenGLVertexArray.h"

namespace Hydron {

	VertexArray* VertexArray::Create()
	{
		switch (Renderer::GetAPI())
		{
			case RendererAPI::None: HYDRON_CORE_ASSERT(false, "RendererAPI::None is currently not supported"); return nullptr;
			case RendererAPI::OpenGL: return new OpenGLVertexArray();
		}

		HYDRON_CORE_ASSERT(false, "Unknown renderer API!");
		return nullptr;
	}

}
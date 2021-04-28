#include "pch.h"
#include "Texture.h"

#include "Renderer.h"
#include "Platform/OpenGL/OpenGLTexture2D.h"

namespace Hydron {


	Ref<Texture2D> Texture2D::Create(const std::string& path)
	{

		switch (Renderer::GetAPI())
		{
			case RendererAPI::API::None: HYDRON_CORE_ASSERT(false, "RendererAPI::None is currently not supported"); return nullptr;
			case RendererAPI::API::OpenGL: return std::make_shared<OpenGLTexture2D>(path);
		}

		HYDRON_CORE_ASSERT(false, "Unknown renderer API!");
		return nullptr;

	}

}
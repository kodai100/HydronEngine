#include "pch.h"
#include "Shader.h"

#include "Renderer.h"
#include "Platform/OpenGL/OpenGLShader.h"

namespace Hydron {



	Shader* Shader::Create(const std::string& filePath)
	{

		switch (Renderer::GetAPI())
		{
			case RendererAPI::API::None: HYDRON_CORE_ASSERT(false, "RendererAPI::None is currently not supported"); return nullptr;
			case RendererAPI::API::OpenGL: return new OpenGLShader(filePath);
		}

		HYDRON_CORE_ASSERT(false, "Unknown renderer API!");
		return nullptr;

	}

	Shader* Shader::Create(const std::string& vertexSrc, const std::string& fragmentSrc)
	{
		switch (Renderer::GetAPI())
		{
			case RendererAPI::API::None: HYDRON_CORE_ASSERT(false, "RendererAPI::None is currently not supported"); return nullptr;
			case RendererAPI::API::OpenGL: return new OpenGLShader(vertexSrc, fragmentSrc);
		}

		HYDRON_CORE_ASSERT(false, "Unknown renderer API!");
		return nullptr;
	}


}
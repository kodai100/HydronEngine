#include "pch.h"
#include "Renderer.h"

#include "Platform/OpenGL/OpenGLShader.h"

namespace Hydron {


	Ref<Camera> Renderer::m_Camera = nullptr;

	void Renderer::Init()
	{
		RenderCommand::Init();
	}

	void Renderer::OnWindowResize(uint32_t width, uint32_t height)
	{
		RenderCommand::SetViewport(0, 0, width, height);
	}


	void Renderer::BeginScene(Ref<Camera> camera)
	{
		m_Camera = camera;
	}

	void Renderer::EndScene()
	{
	}

	void Renderer::Submit(const Ref<Shader>& shader, const Ref<VertexArray>& vertexArray, glm::mat4& transform)
	{
		shader->Bind();
		
		std::dynamic_pointer_cast<OpenGLShader>(shader)->UploadUniformMat4("u_ModelMatrix", transform);
		std::dynamic_pointer_cast<OpenGLShader>(shader)->UploadUniformMat4("u_InvModelMatrix", glm::inverse(transform));
		
		std::dynamic_pointer_cast<OpenGLShader>(shader)->UploadUniformMat4("u_ViewMatrix", m_Camera->GetViewMatrix());
		std::dynamic_pointer_cast<OpenGLShader>(shader)->UploadUniformMat4("u_ProjectionMatrix", m_Camera->GetProjection());
		std::dynamic_pointer_cast<OpenGLShader>(shader)->UploadUniformMat4("u_ViewProjectionMatrix", m_Camera->GetViewProjection());

		std::dynamic_pointer_cast<OpenGLShader>(shader)->UploadUniformFloat3("u_LightDirection", glm::normalize(glm::vec3(-0.5f, -0.5f, -0.5f)));
		std::dynamic_pointer_cast<OpenGLShader>(shader)->UploadUniformFloat3("u_LightColor", glm::normalize(glm::vec3(1.0f, 1.0f, 1.0f)));

		std::dynamic_pointer_cast<OpenGLShader>(shader)->UploadUniformFloat3("u_CameraPos", m_Camera->GetPosition());
		std::dynamic_pointer_cast<OpenGLShader>(shader)->UploadUniformFloat4("u_AmbientColor", glm::vec4(0.01f, 0.01f, 0.01f, 1.0f));

		vertexArray->Bind();
		RenderCommand::DrawIndexed(vertexArray);

	}

}
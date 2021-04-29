#include "pch.h"
#include "Renderer.h"

#include "Platform/OpenGL/OpenGLShader.h"

namespace Hydron {


	Renderer::SceneData* Renderer::m_SceneData = new Renderer::SceneData();

	void Renderer::Init()
	{
		RenderCommand::Init();
	}

	void Renderer::OnWindowResize(uint32_t width, uint32_t height)
	{
		RenderCommand::SetViewport(0, 0, width, height);
	}


	void Renderer::BeginScene(EditorCamera& camera)
	{
		m_SceneData->ViewProjectionMatrix = camera.GetViewProjection();
	}

	void Renderer::EndScene()
	{
	}

	void Renderer::Submit(const Ref<Shader>& shader, const Ref<VertexArray>& vertexArray, Camera& camera, glm::mat4& transform)
	{
		shader->Bind();
		std::dynamic_pointer_cast<OpenGLShader>(shader)->UploadUniformMat4("u_ViewProjection", m_SceneData->ViewProjectionMatrix);
		std::dynamic_pointer_cast<OpenGLShader>(shader)->UploadUniformMat4("u_Transform", transform);
		std::dynamic_pointer_cast<OpenGLShader>(shader)->UploadUniformMat4("u_InvTransform", glm::inverse(transform));
		std::dynamic_pointer_cast<OpenGLShader>(shader)->UploadUniformFloat3("u_LightDirection", glm::normalize(glm::vec3(-0.5f, -0.5f, -0.5f)));
		std::dynamic_pointer_cast<OpenGLShader>(shader)->UploadUniformFloat3("u_CameraPos", camera.GetPosition());
		std::dynamic_pointer_cast<OpenGLShader>(shader)->UploadUniformFloat4("u_AmbientColor", glm::vec4(0.01f, 0.01f, 0.01f, 1.0f));

		vertexArray->Bind();
		RenderCommand::DrawIndexed(vertexArray);

	}

}
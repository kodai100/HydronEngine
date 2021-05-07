#include "pch.h"
#include "Renderer.h"

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

	void Renderer::Submit(const Ref<Mesh>& mesh, glm::mat4& transform)
	{
		mesh->Bind(m_Camera, transform);

		RenderCommand::DrawIndexed(mesh);

	}

}
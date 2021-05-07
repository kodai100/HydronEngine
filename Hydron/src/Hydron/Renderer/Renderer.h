#pragma once

#include "RenderCommand.h"
#include "Hydron/Geometry/Mesh.h"
#include "EditorCamera.h"
#include "Camera.h"

namespace Hydron {

	class Renderer
	{
	public:
		static void Init();

		static void OnWindowResize(uint32_t width, uint32_t height);

		static void BeginScene(Ref<Camera> camera);
		static void EndScene();

		static void Submit(const Ref<Mesh>& mesh, glm::mat4& transform = glm::mat4(1.0f));

		inline static RendererAPI::API GetAPI() { return RendererAPI::GetAPI(); }

	private:
		static Ref<Camera> m_Camera;
	};


}
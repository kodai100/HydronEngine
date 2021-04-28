#pragma once

#include "Base.h"

#include "Window.h"
#include "Hydron/Events/Event.h"
#include "Hydron/Events/ApplicationEvent.h"
#include "LayerStack.h"
#include "Layer.h"

#include "Timestep.h"

#include "Hydron/ImGui/ImGuiLayer.h"

#include "Hydron/Renderer/Shader.h"

namespace Hydron {
	
	class Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();

		void OnEvent(Event& e);

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* layer);

		inline static Application& Get() { return *s_Instance; }
		inline Window& GetWindow() { return *m_Window; }
	private:
		bool OnWindowClose(WindowCloseEvent& e);
		bool OnWindowResize(WindowResizeEvent& e);

	private:
		std::unique_ptr<Window> m_Window;
		ImGuiLayer* m_ImGuiLayer;

		bool m_Running = true;
		bool m_Minimized = false;

		LayerStack m_LayerStack;
		float m_LastFrameTime = 0.0f;

		unsigned int m_VertexArray, m_VertexBuffer, m_IndexBuffer;
		std::unique_ptr<Shader> m_Shader;

	private:
		static Application* s_Instance;
		
	};

	// To be defined in client
	Application* CreateApplication();
}


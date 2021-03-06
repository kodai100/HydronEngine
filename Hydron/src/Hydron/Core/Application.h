#pragma once

#include "Base.h"

#include "Window.h"
#include "Hydron/Events/Event.h"
#include "Hydron/Events/ApplicationEvent.h"
#include "LayerStack.h"
#include "Layer.h"

#include "Timestep.h"

#include "Hydron/ImGui/ImGuiLayer.h"

namespace Hydron {
	
	class Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();

		void Close();

		void OnEvent(Event& e);

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* layer);

		ImGuiLayer* GetImGuiLayer() { return m_ImGuiLayer; }

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

	private:
		static Application* s_Instance;
		
	};

	// To be defined in client
	Application* CreateApplication();
}


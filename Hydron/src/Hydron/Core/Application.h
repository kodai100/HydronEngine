#pragma once

#include "Base.h"
#include "Hydron/Events/Event.h"
#include "Hydron/Events/ApplicationEvent.h"

#include "Window.h"

namespace Hydron {
	
	class HYDRON_API Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();

		void OnEvent(Event& e);

	private:
		bool OnWindowClose(WindowCloseEvent& e);

		std::unique_ptr<Window> m_Window;
		bool m_Running = true;
	};

	// To be defined in client
	Application* CreateApplication();
}


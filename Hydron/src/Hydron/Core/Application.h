#pragma once

#include "Base.h"
#include "Hydron/Events/Event.h"
#include "Window.h"

namespace Hydron {
	
	class HYDRON_API Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();

	private:
		std::unique_ptr<Window> m_Window;
		bool m_Running = true;
	};

	// To be defined in client
	Application* CreateApplication();
}


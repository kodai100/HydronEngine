#pragma once

#include "Core.h"

namespace Hydron {
	
	class HYDRON_API Application
	{
	public:
		Application();
		virtual ~Application();
		void Run();
	};

	// To be defined in client
	Application* CreateApplication();
}


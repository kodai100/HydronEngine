#include "pch.h"

#include "Application.h"

#include "Hydron/Events/ApplicationEvent.h"
#include "Log.h"

namespace Hydron {

	Application::Application() {

	}

	Application::~Application() {

	}

	void Application::Run() {

		WindowResizeEvent e(1280, 720);
		HYDRON_TRACE(e);

		while (true) {
			HYDRON_CORE_INFO("Running")
		}

	}

}
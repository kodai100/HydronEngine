#include "pch.h"

#include "Application.h"

#include "Hydron/Events/ApplicationEvent.h"
#include "Log.h"

namespace Hydron {

	Application::Application()
	{
		m_Window = std::unique_ptr<Window>(Window::Create());
	}

	Application::~Application()
	{

	}

	void Application::Run()
	{

		while (m_Running) {
			m_Window->OnUpdate();
		}

	}

}
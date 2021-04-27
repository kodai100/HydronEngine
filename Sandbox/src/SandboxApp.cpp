#include <Hydron.h>

class ExampleLayer : public Hydron::Layer
{

public:
	ExampleLayer() : Layer("Example Layer") {}
	~ExampleLayer() {}

	void ExampleLayer::OnEvent(Hydron::Event& event)
	{

		if (event.GetEventType() == Hydron::EventType::KeyPressed)
		{

			Hydron::KeyPressedEvent& e = (Hydron::KeyPressedEvent&)event;
			if (e.GetKeyCode() == Hydron::Key::Tab)
			{
				HYDRON_TRACE("Tab key is pressed (event)!");
			}

			HYDRON_TRACE("{0}", (char)e.GetKeyCode());
		}

	}

	void ExampleLayer::OnUpdate(Hydron::Timestep ts)
	{

		if (Hydron::Input::IsKeyPressed(Hydron::Key::Tab))
		{
			HYDRON_TRACE("Tab key is pressed ! (poll)");
		}

	}

};


class Sandbox : public Hydron::Application {
public:
	Sandbox() {
		PushLayer(new ExampleLayer());
	}

	~Sandbox() {

	}
};


Hydron::Application* Hydron::CreateApplication() {
	return new Sandbox();
}
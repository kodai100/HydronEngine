#include <Hydron.h>


class ExampleLayer: public Hydron::Layer {
public:
	ExampleLayer() : Layer("Example")
	{

	}

	void OnUpdate() override
	{
		HYDRON_INFO("ExampleLayer::Update");
	}

	void OnEvent(Hydron::Event& event)
	{
		HYDRON_TRACE("{0}", event);
	}
};

class Sandbox : public Hydron::Application {
public:
	Sandbox() {

		PushLayer(new ExampleLayer());	// deleted inside of layer stack

	}

	~Sandbox() {

	}
};


Hydron::Application* Hydron::CreateApplication() {
	return new Sandbox();
}
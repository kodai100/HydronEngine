#include <Hydron.h>



class Sandbox : public Hydron::Application {
public:
	Sandbox() {

	}

	~Sandbox() {

	}
};


Hydron::Application* Hydron::CreateApplication() {
	return new Sandbox();
}
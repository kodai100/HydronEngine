#pragma once

#include <Hydron.h>

class ExampleLayer : public Hydron::Layer
{

public:
	ExampleLayer() : Layer("Example Layer") {}
	~ExampleLayer() {}

	void OnUpdate(Hydron::Timestep ts) override;
	void OnEvent(Hydron::Event& event) override;

};


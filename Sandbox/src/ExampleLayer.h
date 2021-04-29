#pragma once

#include "Hydron.h"

#include "Snow/SnowSimulation.h"

class ExampleLayer : public Hydron::Layer
{


public:
	ExampleLayer();

	~ExampleLayer() {}

	void OnUpdate(Hydron::Timestep ts);

	void OnEvent(Hydron::Event& e) override;

	void OnImGuiRender();

private:
	float t = 0;

	SnowSimulation* snowSimulation;

	float m_CameraMoveSpeed = 1;
	glm::vec4 m_Color;

	Hydron::Ref<Hydron::Texture2D> m_Texture, m_AlphaTexture;

	Hydron::ShaderLibrary m_ShaderLibrary;

	Hydron::Ref<Hydron::FrameBuffer> m_FrameBuffer;

	Hydron::Ref<Hydron::Mesh> m_Mesh;

	bool m_ViewportFocused = false, m_ViewportHovered = false;
	glm::vec2 m_ViewportSize = { 0.0f, 0.0f };
	glm::vec2 m_ViewportBounds[2];

	Hydron::EditorCamera m_EditorCamera;

};
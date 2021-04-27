#pragma once


#include "Hydron/Core/Layer.h"


namespace Hydron {

	class ImGuiLayer : public Layer
	{

	public:
		ImGuiLayer();
		~ImGuiLayer() = default;

		void OnAttach();
		void OnDetach();
		void OnEvent(Event& event);

		void Begin();
		void End();

		void BlockEvents(bool block) { m_BlockEvents = block; }

		void SetDarkThemeColors();
	private:
		bool m_BlockEvents = true;
		float m_Time = 0.0f;
	};

}
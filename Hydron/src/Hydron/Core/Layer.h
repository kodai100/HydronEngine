#pragma once

#include "Hydron/Core/Base.h"
#include "Hydron/Core/Timestep.h"
#include "Hydron/Events/Event.h"

namespace Hydron {


	class Layer
	{

	public:
		Layer(const std::string& name = "Layer");
		virtual ~Layer();

		virtual void OnAttach() {}
		virtual void OnDetach() {}
		virtual void OnUpdate(Timestep ts) {}
		virtual void OnImGuiRender() {}
		virtual void OnEvent(Event& event) {}

		inline const std::string& GetName() const { return m_DebugName; }

	private:
		std::string m_DebugName;
	};



}

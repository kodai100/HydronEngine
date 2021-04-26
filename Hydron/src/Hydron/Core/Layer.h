#pragma once

#include "Hydron/Core/Base.h"
#include "Hydron/Events/Event.h"

namespace Hydron {


	class HYDRON_API Layer
	{

	public:
		Layer(const std::string& name = "Layer");
		virtual ~Layer();

		virtual void OnAttatch() {}
		virtual void OnDetatch() {}
		virtual void OnUpdate() {}
		virtual void OnEvent(Event& event) {}

		inline const std::string& GetName() const { return m_DebugName; }

	private:
		std::string m_DebugName;
	};



}

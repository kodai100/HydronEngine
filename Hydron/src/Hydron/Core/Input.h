#pragma once

#include "Hydron/Core/Base.h"

#include "Hydron/Core/KeyCodes.h"
#include "Hydron/Core/MouseCodes.h"

namespace Hydron {

	class HYDRON_API Input
	{
	public:
		static bool IsKeyPressed(KeyCode keyCode);

		static bool IsMouseButtonPressed(MouseCode button);
		static std::pair<float, float> GetMousePosition();
		static float GetMouseX();
		static float GetMouseY();

	};

}
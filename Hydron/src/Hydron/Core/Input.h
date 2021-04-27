#pragma once

#include "Hydron/Core/Base.h"

#include "Hydron/Core/KeyCodes.h"
#include "Hydron/Core/MouseCodes.h"

#include "glm/vec2.hpp"

namespace Hydron {

	class HYDRON_API Input
	{
	public:
		static bool IsKeyPressed(KeyCode keyCode);

		static bool IsMouseButtonPressed(MouseCode button);
		static glm::vec2 GetMousePosition();
		static float GetMouseX();
		static float GetMouseY();

	};

}
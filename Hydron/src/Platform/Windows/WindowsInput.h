#pragma once

#include "Hydron/Core/Input.h"

namespace Hydron {

	class WindowsInput : public Input
	{

	protected:
		bool IsKeyPressedImpl(int keyCode) override;

		bool IsMouseButtonPressedImpl(int button) override;
		std::pair<float, float> GetMousePositionImpl() override;
		float GetMouseXImpl() override;
		float GetMoyseYImpl() override;
	};


}

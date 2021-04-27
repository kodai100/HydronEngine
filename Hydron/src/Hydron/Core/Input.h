#pragma once

#include "Hydron/Core/Base.h"

namespace Hydron {

	class HYDRON_API Input
	{
	public:
		inline static bool IsKeyPressed(int keyCode) { return s_Instance->IsKeyPressedImpl(keyCode); }

		inline static bool IsMouseButtonPressed(int button) { return s_Instance->IsMouseButtonPressedImpl(button); }
		inline static std::pair<float, float> GetMousePosition() { return s_Instance->GetMousePositionImpl(); }
		inline static float GetMouseX() { return s_Instance->GetMouseXImpl(); }
		inline static float GetMouseY() { return s_Instance->GetMoyseYImpl(); }

	protected:
		virtual bool IsKeyPressedImpl(int keyCode) = 0;

		virtual bool IsMouseButtonPressedImpl(int button) = 0;
		virtual std::pair<float, float> GetMousePositionImpl() = 0;
		virtual float GetMouseXImpl() = 0;
		virtual float GetMoyseYImpl() = 0;

	private:
		static Input* s_Instance;
	};

}
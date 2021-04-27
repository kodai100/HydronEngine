#include "pch.h"
#include "WindowsInput.h"

#include "Hydron/Core/Application.h"

#include <GLFW/glfw3.h>

namespace Hydron {


	Input* Input::s_Instance = new WindowsInput();	// instantiate this position (not inside window init) because input is non-data class 

	bool WindowsInput::IsKeyPressedImpl(int keyCode)
	{
		auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());

		auto state = glfwGetKey(window, keyCode);

		return state == GLFW_PRESS || state == GLFW_REPEAT;
	}


	bool WindowsInput::IsMouseButtonPressedImpl(int button)
	{
		auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
		auto state = glfwGetMouseButton(window, button);
		return state == GLFW_PRESS;
	}

	std::pair<float, float> WindowsInput::GetMousePositionImpl()
	{
		auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
		double xPos, yPos;
		glfwGetCursorPos(window, &xPos, &yPos);
		return { (float)xPos, (float)yPos };
	}

	float WindowsInput::GetMouseXImpl()
	{
		auto[x, y] = GetMousePosition();
		return x;
	}

	float WindowsInput::GetMoyseYImpl()
	{
		auto [x, y] = GetMousePosition();
		return y;
	}

}
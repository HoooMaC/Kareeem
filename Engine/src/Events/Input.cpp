#include "Core/KRMpch.h"

#include "Input.h"

#include "OpenGL/OpenGLContext.h"

#include <GLFW/glfw3.h>

namespace krm {

	bool Input::IsKeyPressed(int keycode)
	{
		GLFWwindow* window = OpenGLContext::getCurrentContext();
		int state = glfwGetKey(window, keycode);
		return state == GLFW_PRESS || state == GLFW_REPEAT;
	}

	bool Input::IsMouseButtonPressed(int button)
	{
		GLFWwindow* window = OpenGLContext::getCurrentContext();
		int state = glfwGetMouseButton(window, button);
		return state == GLFW_PRESS;
	}

	std::pair<float, float> Input::GetMousePosition()
	{
		GLFWwindow* window = OpenGLContext::getCurrentContext();
		double xpos, ypos;
		glfwGetCursorPos(window, &xpos, &ypos);

		return { (float)xpos, (float)ypos };
	}

	float Input::GetMouseX()
	{
		auto [x, y] = GetMousePosition();
		return x;
	}

	float Input::GetMouseY()
	{
		auto [x, y] = GetMousePosition();
		return y;
	}

}
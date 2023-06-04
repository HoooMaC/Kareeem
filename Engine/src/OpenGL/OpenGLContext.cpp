#include "Core/KRMpch.h"

#include "OpenGLContext.h"

#include <GLFW/glfw3.h>

namespace krm {

	GLFWwindow* OpenGLContext::current;

	void OpenGLContext::setContext(GLFWwindow* window)
	{
		current = window;
		glfwMakeContextCurrent(current);
	}

	GLFWwindow* OpenGLContext::getCurrentContext()
	{
		return current;
	}

	void OpenGLContext::swapBuffer()
	{
		glfwSwapBuffers(current);
	}

	void OpenGLContext::destroyContext()
	{
		glfwDestroyWindow(current);
	}

}
#pragma once

struct GLFWwindow;

namespace krm {

	class OpenGLContext
	{
	public:
		static void setContext(GLFWwindow* window);
		static GLFWwindow* getCurrentContext();
		static void swapBuffer();
		static void destroyContext();
	private:
		static GLFWwindow* current;
	};

}
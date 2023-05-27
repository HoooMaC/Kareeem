#pragma once
#include "KRMpch.h"

#include "Events\ApplicationEvent.h"
#include "Events\KeyEvent.h"
#include "Events\MouseEvent.h"
#include <GLFW\glfw3.h>
namespace krm {

	class Application
	{
	public:
		Application(const std::string& name = "OpenGL Sandbox", uint32_t width = 1280, uint32_t height = 720);
		virtual ~Application();

		void Run();

		void OnEvent(Event& e);
	private:
		bool OnWindowClose(WindowCloseEvent& e);
	private:
		GLFWwindow* m_Window;
		bool m_Running = true;
	private:
	};

}

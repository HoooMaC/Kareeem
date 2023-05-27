#include "Core\KRMpch.h"
#include "Core\Core.h"
#include "Application.h"

namespace krm {

	
	Application::Application(const std::string& name, uint32_t width, uint32_t height)
	{
		glfwInit();
		m_Window = glfwCreateWindow(1280, 720, "Window test", NULL, NULL);
		glfwMakeContextCurrent(m_Window);
	}

	Application::~Application()
	{
		glfwDestroyWindow(m_Window);
		glfwTerminate();
	}

	void Application::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowCloseEvent>(KRM_BIND_EVENT_FN(Application::OnWindowClose));

		//HZ_CORE_TRACE("{0}", e);
	}

	void Application::Run()
	{
		while (m_Running)
		{
			glClear(GL_COLOR_BUFFER_BIT);
			glClearColor(0.8, 0.2, 0.3, 1.0);
			glfwSwapBuffers(m_Window);

			glfwPollEvents();
		}
	}

	bool Application::OnWindowClose(WindowCloseEvent& e)
	{
		m_Running = false;
		return true;
	}

}
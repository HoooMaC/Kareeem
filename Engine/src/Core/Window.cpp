#include "Core\KRMpch.h"
#include "Core\Window.h"
#include "Core\Log.h"

#include "Events\KeyEvent.h"
#include "Events\MouseEvent.h"
#include "Events\ApplicationEvent.h"

#include <GLEW\glew.h>
#include <GLFW\glfw3.h>

namespace krm {

	static bool s_GLFWInitialized = false;

	Window::Window(WindowProps prop)
	{
		m_Data.Title = prop.Title;
		m_Data.Width = prop.Width;
		m_Data.Height = prop.Height;

		KRM_LOG_CORE_INFO("Creating window {0} ({1}, {2})", prop.Title, prop.Width, prop.Height);

		if (!s_GLFWInitialized)
		{
			// TODO: glfwTerminate on system shutdown
			if(!glfwInit())
			{
				glfwSetErrorCallback([](int error, const char* message) 
					{ 
						KRM_LOG_CORE_ERROR("Failed to Initialized GLFW");
						KRM_LOG_CORE_ERROR("GLFW Error : ({0}), ({1})", error, message);
					}
				);
			}

		}

		m_Window = glfwCreateWindow((int)prop.Width, (int)prop.Height, m_Data.Title.c_str(), nullptr, nullptr);
		glfwMakeContextCurrent(m_Window);
		glfwSetWindowUserPointer(m_Window, &m_Data);
		setVSync(true);

		if (!s_GLFWInitialized)
		{

			if (glewInit() != GLEW_OK)
			{
				KRM_LOG_CORE_ERROR("Error to initialized GLEW");
			}

			s_GLFWInitialized = true;
		}

		KRM_LOG_CORE_INFO("{}", reinterpret_cast<const char*>(glGetString(GL_VERSION)));

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		// Set GLFW callbacks
		glfwSetWindowSizeCallback(m_Window, [](GLFWwindow* window, int width, int height)
		{
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
			data.Width = width;
			data.Height = height;

			WindowResizeEvent event(width, height);
			data.EventCallback(event);
		});

		glfwSetWindowCloseCallback(m_Window, [](GLFWwindow* window) 
		{
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
			WindowCloseEvent event;
			data.EventCallback(event);
		});

		glfwSetKeyCallback(m_Window, [](GLFWwindow* window, int key, int scancode, int action, int mods)
		{
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

			switch (action)
			{
				case GLFW_PRESS:
				{
					KeyPressedEvent event(key, 0);
					data.EventCallback(event);
					break;
				}
				case GLFW_RELEASE:
				{
					KeyReleasedEvent event(key);
					data.EventCallback(event);
					break;
				}
				case GLFW_REPEAT:
				{
					KeyPressedEvent event(key, 1);
					data.EventCallback(event);
					break;
				}
			}
		});

		glfwSetMouseButtonCallback(m_Window, [](GLFWwindow* window, int button, int action, int mods)
		{
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

			switch (action)
			{
				case GLFW_PRESS:
				{
					MouseButtonPressedEvent event(button);
					data.EventCallback(event);
					break;
				}
				case GLFW_RELEASE:
				{
					MouseButtonReleasedEvent event(button);
					data.EventCallback(event);
					break;
				}
			}
		});

		glfwSetScrollCallback(m_Window, [](GLFWwindow* window, double xOffset, double yOffset)
		{
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

			MouseScrolledEvent event((float)xOffset, (float)yOffset);
			data.EventCallback(event);
		});

		glfwSetCursorPosCallback(m_Window, [](GLFWwindow* window, double xPos, double yPos)
		{
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

			MouseMovedEvent event((float)xPos, (float)yPos);
			data.EventCallback(event);
		});
	}

	Window::~Window() 
	{
		glfwDestroyWindow(m_Window);
	}

	void Window::onUpdate()
	{
		glfwPollEvents();
		glfwSwapBuffers(m_Window);
	}

	void Window::setVSync(bool enable)
	{
		if (enable)
			glfwSwapInterval(1);
		else
			glfwSwapInterval(0);

		m_Data.VSync = enable;
	}

}
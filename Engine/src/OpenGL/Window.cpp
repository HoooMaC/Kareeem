#include "Core\KRMpch.h"

#include "Window.h"

#include "Core\Log.h"

#include "Events\KeyEvent.h"
#include "Events\MouseEvent.h"
#include "Events\ApplicationEvent.h"

#include "OpenGL\OpenGLContext.h"

#include <GLEW\glew.h>
#include <GLFW\glfw3.h>

static bool s_Initialized = false;

namespace krm {


	Window::Window(WindowProps prop)
	{
		m_Data.Title = prop.Title;
		m_Data.Width = prop.Width;
		m_Data.Height = prop.Height;

		KRM_LOG_CORE_INFO("Creating window {0} ({1}, {2})", prop.Title, prop.Width, prop.Height);

		if (!s_Initialized)
		{
			int result = glfwInit();
			if(result)
				m_Window = glfwCreateWindow((int)prop.Width, (int)prop.Height, m_Data.Title.c_str(), nullptr, nullptr);
			else
			{
				KRM_LOG_CORE_ERROR("Failed to initialized GLFW");
				ASSERT(false);
			}
		}	

		OpenGLContext::setContext(m_Window);

		if (!s_Initialized)
		{
			GLenum result = glewInit();
			if (result != GLEW_OK)
			{
				KRM_LOG_CORE_ERROR("Failed to Initialized GLEW");
				ASSERT(false);
				OpenGLContext::destroyContext();
			}
			s_Initialized = true;
		}

		glfwSetWindowUserPointer(m_Window, &m_Data);
		setVSync(true);

		//glEnable(GL_BLEND);
		//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

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
		OpenGLContext::swapBuffer();
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
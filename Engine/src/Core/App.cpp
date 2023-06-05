
#include "Core/KRMpch.h"
#include "Core/App.h"
#include "Core/Core.h"
#include "Core/Log.h"
#include "Core/Renderer/Renderer.h"
#include "Core/Renderer/RendererCommand.h"

#include "OpenGL/Mesh/Shader.h"
#include "OpenGL/OpenGLContext.h"

#include "Events/Event.h"
#include "Events/Input.h"
#include "Events/KeyCodes/KeyCodes.h"

#include <imgui.h>
#include <backends/imgui_impl_opengl3.h>
#include <backends/imgui_impl_glfw.h>

#include <GLFW/glfw3.h>

namespace krm {

	App::App(Window* window)
	{
		m_Window = window;
		m_Window->setEventCallback(BIND_EVENT_FN(App::eventHandle));
		KRM_LOG_CORE_INFO("OpenGL Info:");
		KRM_LOG_CORE_INFO("  Vendor: {0}",   reinterpret_cast<const char*>(glGetString(GL_VENDOR)));
		KRM_LOG_CORE_INFO("  Renderer: {0}", reinterpret_cast<const char*>(glGetString(GL_RENDERER)));
		KRM_LOG_CORE_INFO("  Version: {0}",  reinterpret_cast<const char*>(glGetString(GL_VERSION)));
		
	}

	App::~App()
	{
	}

	void App::eventHandle(Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(App::OnWindowClose));

		KRM_LOG_CORE_TRACE("{0}", e);

		for (auto it = m_LayerStack.rend(); it != m_LayerStack.rbegin(); ++it )
		{
			(*it)->eventHandle(e);
			if (e.Handled)
				break;
		}
	}

	void App::run()
	{
		while (m_Running)
		{
			float time = (float)glfwGetTime();
			TimeStep ts = time - m_LastFrameTime;
			m_LastFrameTime = time;

			for (Layer* layer : m_LayerStack)
				layer->OnUpdate(ts);	

			m_Window->onUpdate();
		}
	}

	void App::PushLayer(Layer* layer)
	{
		m_LayerStack.PushLayer(layer);
	}

	void App::PushOverlay(Layer* layer)
	{
		m_LayerStack.PushOverlay(layer);
	}

	bool App::OnWindowClose(WindowCloseEvent& e)
	{
		m_Running = false;
		return true;
	}

	bool App::OnKeyPressed(KeyPressedEvent& e)
	{
		return true;
	}


}
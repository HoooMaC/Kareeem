#pragma once
#include "KRMpch.h"

#include "Core\Window.h"

#include "Core\Layer\LayerStack.h"

#include "Events\Event.h"
#include "Events\ApplicationEvent.h"
#include "Events\KeyEvent.h"
#include "Events\MouseEvent.h"

#include "OpenGL\Mesh\VertexArray.h"
#include "OpenGL\Mesh\Buffer.h"

//this is temporary
struct GLFWwindow;

namespace krm {

	class App
	{
	//this is also temporary, just for testing imgui
	public:
		GLFWwindow* m_Window;
	public:
		App(const std::string& name = "OpenGL Sandbox", uint32_t width = 1280, uint32_t height = 720);
		virtual ~App();

		void run();

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* layer);

		void eventHandle(Event& e);
	private:
		bool OnWindowClose(WindowCloseEvent& e);
	private:
		LayerStack m_LayerStack;
		Window myWindow;

		bool m_Running = true;
		VertexArray m_VertexArray;
		VertexBuffer m_VertexBuffer;
	};

}

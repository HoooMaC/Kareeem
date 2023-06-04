#pragma once
#include "KRMpch.h"

#include "OpenGl\Window.h"

#include "Core\Layer\LayerStack.h"

#include "Events\Event.h"
#include "Events\ApplicationEvent.h"
#include "Events\KeyEvent.h"
#include "Events\MouseEvent.h"

#include "OpenGL\Mesh\VertexArray.h"
#include "OpenGL\Mesh\Buffer.h"

namespace krm {

	class App
	{
	public:
		App(Window* window);
		virtual ~App();

		void run();

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* layer);

		void eventHandle(Event& e);
	private:
		bool OnWindowClose(WindowCloseEvent& e);
	private:
		LayerStack m_LayerStack;
		Window* m_Window;

		bool m_Running = true;
		VertexArray m_VertexArray;
		};

}

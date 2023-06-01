#pragma once
#include "KRMpch.h"

#include "Core\Window.h"

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
		App(const std::string& name = "OpenGL Sandbox", uint32_t width = 1280, uint32_t height = 720);
		virtual ~App();

		void run();

		void eventHandle(Event& e);
	private:
		bool OnWindowClose(WindowCloseEvent& e);
	private:
		Window myWindow;
		bool m_Running = true;
		VertexArray m_VertexArray;
		VertexBuffer m_VertexBuffer;
		IndexBuffer m_IndexBuffer;
	};

}

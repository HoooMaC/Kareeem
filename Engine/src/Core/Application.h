#pragma once
#include "KRMpch.h"

#include "Window.h"

#include "Events\ApplicationEvent.h"
#include "Events\KeyEvent.h"
#include "Events\MouseEvent.h"

namespace krm {

	class Application
	{
	public:
		Application(const std::string& name = "OpenGL Sandbox", uint32_t width = 1280, uint32_t height = 720);
		virtual ~Application() = default;

		void Run();

		void OnEvent(Event& e);

		//void PushLayer(Layer* layer);
		//void PushOverlay(Layer* layer);

		inline Window& GetWindow() { return *m_Window; }

		inline static Application& Get() { return *s_Instance; }
	private:
		bool OnWindowClose(WindowCloseEvent& e);
	private:
		std::unique_ptr<Window> m_Window;
		bool m_Running = true;
	private:
		static Application* s_Instance;
	};

}
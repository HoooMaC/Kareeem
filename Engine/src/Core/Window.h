#pragma once

#include "KRMpch.h"
#include "GLFW\glfw3.h"

#include "Events\Event.h"

namespace krm {

	struct WindowProps
	{
		std::string Title;
		uint32_t Width;
		uint32_t Height;

		WindowProps(const std::string& title = "OpenGL Sandbox", uint32_t width = 1280, uint32_t height = 720)
			: Title(title), Width(width), Height(height) { }
	};	

	// Interface representing a desktop system based Window
	class Window
	{
	public:
		static Window* Create(const WindowProps& props = WindowProps());
	public:
		using EventCallbackFn = std::function<void(Event&)>;

		inline Window(const WindowProps& props) { Init(props); }
		inline ~Window() { Shutdown(); }

		void OnUpdate()
		{
			glfwPollEvents();
			glfwSwapBuffers(m_Window);
		}

		// Window attributes
		inline void SetEventCallback(const EventCallbackFn& callback) { m_Data.EventCallback = callback; }
		inline void SetVSync(bool enabled);

		inline bool IsVSync() const { return m_Data.VSync; }
		inline uint32_t GetWidth() const { return m_Data.Width; }
		inline uint32_t GetHeight() const { return m_Data.Height; }
		inline void* GetNativeWindow() const { return m_Window; }

	private:
		void Init(const WindowProps& props);
		void Shutdown() { glfwDestroyWindow(m_Window); }
	private:
		GLFWwindow* m_Window;

		struct WindowData
		{
			std::string Title;
			uint32_t Width, Height;
			bool VSync;

			EventCallbackFn EventCallback;
		};

		WindowData m_Data;
	};

}
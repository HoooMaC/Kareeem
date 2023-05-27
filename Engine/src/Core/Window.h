#pragma once

#include "Core\KRMpch.h"

#include "Events\Event.h"

struct GLFWwindow;

namespace krm {

	struct WindowProps
	{
		std::string Title;
		unsigned int Width;
		unsigned int Height;

		WindowProps(const std::string& title = "Hazel Engine",
			unsigned int width = 1280,
			unsigned int height = 720)
			: Title(title), Width(width), Height(height)
		{
		}
	};

	class Window
	{
	public:
		using EventCallbackFn = std::function<void(Event&)>;
		Window(WindowProps prop);
		~Window();
		void onUpdate();
		void setVSync(bool enabled);
		void setColor(float r, float g, float b, float a);

		inline void setEventCallback(const EventCallbackFn& callback) { m_Data.EventCallback = callback; }

		inline unsigned int getWidth() const { return m_Data.Width; }
		inline unsigned int getHeight() const { return m_Data.Height; }

	private:
		struct WindowData
		{
			std::string Title;
			unsigned int Width, Height;
			bool VSync;

			EventCallbackFn EventCallback;
		};
		GLFWwindow* m_Window;
		WindowData m_Data;
	};

}

#include "Core\KRMpch.h"
#include "Core\App.h"
#include "Core\Core.h"
#include "Core\Log.h"

#include "Events\Event.h"

namespace krm {

	App::App(const std::string& name, uint32_t width, uint32_t height)
		: myWindow({name, width, height})
	{
		myWindow.setEventCallback(BIND_EVENT_FN(App::eventHandle));
	}

	App::~App()
	{
	}

	void App::eventHandle(Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(App::OnWindowClose));

		KRM_LOG_CORE_TRACE("{0}", e);
	}

	void App::run()
	{
		while (m_Running)
		{
			myWindow.onUpdate();
			myWindow.setColor(0.8f, 0.1f, 0.2f, 1.0f);
		}
	}

	bool App::OnWindowClose(WindowCloseEvent& e)
	{
		m_Running = false;
		return true;
	}

}
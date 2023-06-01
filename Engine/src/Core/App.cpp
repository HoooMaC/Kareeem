
#include "Core\KRMpch.h"
#include "Core\App.h"
#include "Core\Core.h"
#include "Core\Log.h"

#include "OpenGL\Mesh\Shader.h"

#include "Events\Event.h"

#include "GLFW\glfw3.h"

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

		Vertex vertices[] = {
			{ {-0.5f, -0.5f, 0.0f }, { 1.0f, 1.0f, 1.0f, 1.0f }, { 0.0f, 0.0f }, 1.0f },
			{ { 0.5f, -0.5f, 0.0f }, { 1.0f, 1.0f, 1.0f, 1.0f }, { 1.0f, 0.0f }, 1.0f },
			{ { 0.0f,  0.5f, 0.0f }, { 1.0f, 1.0f, 1.0f, 1.0f }, { 0.5f, 0.5f }, 1.0f }
		};

		unsigned int indices[] = { 0,1,2 };

		Shader defaultShader("Resource/Shader/default/default.vert.shader", "Resource/Shader/default/default.frag.shader");

		m_VertexArray.bind();
		m_VertexArray.setVertexArray();

		m_VertexBuffer.bind();
		m_VertexBuffer.inputData(vertices, 3);
		m_VertexBuffer.setData();


		m_IndexBuffer.bind();
		m_IndexBuffer.inputData(indices, 3);
		m_IndexBuffer.setData();

		m_VertexArray.unbind();


		while (m_Running)
		{
			//RendererCommand::ClearColor(0.1f, 0.1f, 0.1f, 0.1f);
			glClear(GL_COLOR_BUFFER_BIT);
			glClearColor(0.1f, 0.1f, 0.1f, 0.1f);

			//Renderer::BeginScene();


			m_VertexArray.bind();
			defaultShader.bind();


			//Renderer::Submit();
			glDrawElements(GL_TRIANGLES, m_IndexBuffer.GetCount(), GL_UNSIGNED_INT, nullptr);




			//Renderer::EndScene();

			myWindow.onUpdate();
		}
	}

	bool App::OnWindowClose(WindowCloseEvent& e)
	{
		m_Running = false;
		return true;
	}

}

#include "Core\KRMpch.h"
#include "Core\App.h"
#include "Core\Core.h"
#include "Core\Log.h"
#include "Core\Renderer\Renderer.h"
#include "Core\Renderer\RendererCommand.h"

#include "OpenGL\Mesh\Shader.h"
#include "OpenGL\OpenGLContext.h"

#include "Events\Event.h"

#include <imgui.h>
#include <backends/imgui_impl_opengl3.h>
#include <backends/imgui_impl_glfw.h>

namespace krm {

	App::App(Window* window)
	{
		m_Window = window;
		m_Window->setEventCallback(BIND_EVENT_FN(App::eventHandle));
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
			(*it)->OnEvent(e);
			if (e.Handled)
				break;
		}
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

		glm::vec4 Color({ 1.0f, 0.1f, 0.8f, 1.0f });

		glm::mat4 projection = glm::ortho(0.0f, 3.2f * 3, 0.0f, 1.8f * 3);

		glm::mat4 view(0.5f);
		glm::vec3 position(1.0f);
		glm::mat4 model = glm::translate(glm::mat4(1.0f), position);
		glm::mat4 pv = projection * view * model;

		float arrray[3] = { 1,1,1 };
		defaultShader.uploadUniform("u_Color", glm::value_ptr(Color));
		defaultShader.uploadUniform("pv", glm::value_ptr(pv));
		defaultShader.uploadUniform("arrray", arrray);

		m_VertexArray.setVertexArray();

		m_VertexArray.addDatatoVertexBuffer(0, vertices, 3);
		m_VertexArray.addDatatoIndexBuffer(indices, 3);

		while (m_Running)
		{

			RendererCommand::Clear();
			RendererCommand::setClearColor({ 0.1f, 0.1f, 0.1f, 0.1f });

			Renderer::beginScene();

			//shader. addUniform  --- yaaaa sesuatu yang seperti inilah
			Renderer::draw(defaultShader, m_VertexArray);



			//shader.flush --- untuk menghapus semua Uniform List (tapi ini optional)
			//bisa juga pake check condition apabila shader udah ada maka hanya perlu updata data atau tidak lakukan apa-apa

			Renderer::endScene();

			for (Layer* layer : m_LayerStack)
				layer->OnUpdate();

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


}
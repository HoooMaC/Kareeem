
#include "Core\KRMpch.h"
#include "Core\App.h"
#include "Core\Core.h"
#include "Core\Log.h"
#include "Core\Renderer\Renderer.h"
#include "Core\Renderer\RendererCommand.h"

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

		m_VertexArray.setVertexArray();

		m_VertexArray.addDatatoVertexBuffer(0, vertices, 3);
		m_VertexArray.addDatatoIndexBuffer(indices, 3);

		m_VertexArray.unbind();


		glm::vec4 u_Color({ 0.4f, 0.1f, 0.8f, 1.0f });
		defaultShader.addNewUniform("u_Color", UniformType::Float4, 1, glm::value_ptr(u_Color));
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

			myWindow.onUpdate();
		}
	}

	bool App::OnWindowClose(WindowCloseEvent& e)
	{
		m_Running = false;
		return true;
	}

}
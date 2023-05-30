
#include "Core\KRMpch.h"
#include "Core\App.h"
#include "Core\Core.h"
#include "Core\Log.h"

#include "Events\Event.h"

#include <GLEW\glew.h>
#include "GLFW\glfw3.h"

namespace krm {

	App::App(const std::string& name, uint32_t width, uint32_t height)
		//: myWindow({name, width, height})
	{
		//myWindow.setEventCallback(BIND_EVENT_FN(App::eventHandle));
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
		////buat vertex Array
		//VertexArray m_va;

		////atur data pada index buffer dan pada vertex buffer
		////masukkan alamat dari datanya untuk index buffer dan untuk vertex buffer
		//m_va.setData();

		// TODO: glfwTerminate on system shutdown
		if (!glfwInit())
		{
			glfwSetErrorCallback([](int error, const char* message)
				{
					KRM_LOG_CORE_ERROR("Failed to Initialized GLFW");
					KRM_LOG_CORE_ERROR("GLFW Error : ({0}), ({1})", error, message);
				}
			);
		}


		GLFWwindow* window = glfwCreateWindow((int)1280, (int)720, "window test", nullptr, nullptr);
		glfwMakeContextCurrent(window);

		if (glewInit() != GLEW_OK)
		{
			KRM_LOG_CORE_ERROR("FAILED TO INITIALZED GLEW");
		}

		Vertex vertices[] = {
			{ {-0.5f, -0.5f, 0.0f }, { 1.0f, 1.0f, 1.0f, 1.0f }, { 0.0f, 0.0f }, 1.0f },
			{ { 0.5f, -0.5f, 0.0f }, { 1.0f, 1.0f, 1.0f, 1.0f }, { 1.0f, 0.0f }, 1.0f },
			{ { 0.0f,  1.0f, 0.0f }, { 1.0f, 1.0f, 1.0f, 1.0f }, { 0.5f, 0.5f }, 1.0f }
		};

		unsigned int indices[] = { 0,1,2 };

		unsigned int va, vb, ib;

		glGenVertexArrays(1, &va);
		glBindVertexArray(va);

		glGenBuffers(1, &vb);
		glBindBuffer(GL_ARRAY_BUFFER, vb);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void*)OFFSETOF(Vertex,position));

		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void*)OFFSETOF(Vertex,color));

		glEnableVertexAttribArray(2);
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void*)OFFSETOF(Vertex,texCoord));

		glEnableVertexAttribArray(3);
		glVertexAttribPointer(3, 1, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void*)OFFSETOF(Vertex,texIndex));

		glGenBuffers(1, &ib);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ib);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

		//glBindVertexArray(0);
		//glBindBuffer(GL_ARRAY_BUFFER, 0);
		//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

		while (m_Running)
		{
			glBindVertexArray(va);
			glClear(GL_COLOR_BUFFER_BIT);
			glClearColor(0.1, 0.1f, 0.1f, 0.1f);

			//RendererCommand::Draw();
			glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, nullptr);
			//myWindow.onUpdate();
			glfwPollEvents();
			glfwSwapBuffers(window);
		}
	}

	bool App::OnWindowClose(WindowCloseEvent& e)
	{
		m_Running = false;
		return true;
	}

}
#include "SandboxApp.h"

#include "Core/Camera/TimeStep.h"
#include "Core/Renderer/Renderer.h"
#include "Core/Renderer/RendererCommand.h"
#include "Events/KeyCodes/KeyCodes.h"
#include "Events/Input.h"
#include <GLFW/glfw3.h>

#include <imgui.h>
#include <backends/imgui_impl_opengl3.h>
#include <backends/imgui_impl_glfw.h>

ClientLayer::ClientLayer()
	: Layer("Example"), m_CameraController((float)1280 / 720, true)
{
	Vertex vertices[] = {
		{ {-1.0f, -1.0f, 0.0f }, { 0.5f, 0.0f, 1.0f, 1.0f }, { 0.0f, 0.0f }, 1.0f },
		{ { 1.0f, -1.0f, 0.0f }, { 0.5f, 0.0f, 1.0f, 1.0f }, { 1.0f, 0.0f }, 1.0f },
		{ { 1.0f,  1.0f, 0.0f }, { 0.5f, 0.0f, 1.0f, 1.0f }, { 1.0f, 1.0f }, 1.0f },
		{ {-1.0f,  1.0f, 0.0f }, { 0.5f, 0.0f, 1.0f, 1.0f }, { 0.0f, 1.0f }, 1.0f }
	};

	unsigned int indices[] = { 0,1,2,2,3,0 };

	defaultShader = std::make_unique<krm::Shader>("Resource/Shader/default/default.vert.shader", "Resource/Shader/default/default.frag.shader");
	m_VertexArray = std::make_unique<krm::VertexArray>();

	position = glm::vec3{ 0.0f, 0.0f, 0.0f };

	model = glm::translate(glm::mat4(1.0f), position);

	glm::mat4 pv = m_CameraController.GetCamera().GetViewProjectionMatrix();

	defaultShader->uploadUniform("model", glm::value_ptr(model));
	defaultShader->uploadUniform("pv", glm::value_ptr(pv));

	m_VertexArray->setVertexArray();

	m_VertexArray->addDatatoVertexBuffer(vertices, 4);
	m_VertexArray->addDatatoIndexBuffer(indices, 6);
}

void ClientLayer::OnUpdate(krm::TimeStep ts)
{
	m_CameraController.OnUpdate(ts);

	krm::RendererCommand::Clear();
	krm::RendererCommand::setClearColor({ 1.0f, 0.1f, 0.1f, 0.1f });

	krm::Renderer::beginScene();

	defaultShader->uploadUniform("pv", glm::value_ptr(m_CameraController.GetCamera().GetViewProjectionMatrix()));
	model = glm::translate(glm::mat4(1.0f), position);
	defaultShader->uploadUniform("model", glm::value_ptr(model));

	//shader. addUniform  --- yaaaa sesuatu yang seperti inilah
	krm::Renderer::draw(defaultShader, m_VertexArray);



	//shader.flush --- untuk menghapus semua Uniform List (tapi ini optional)
	//bisa juga pake check condition apabila shader udah ada maka hanya perlu updata data atau tidak lakukan apa-apa

	krm::Renderer::endScene();
}

void ClientLayer::OnImGuiRender()
{
}

void ClientLayer::eventHandle(krm::Event& e)
{
	m_CameraController.eventHandle(e);
}




#include "SandboxApp.h"

#include "Core/Camera/TimeStep.h"

#include "Core/Renderer/Renderer2D.h"
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
	krm::Renderer2D::init();
}

void ClientLayer::OnUpdate(krm::TimeStep ts)
{
	m_CameraController.OnUpdate(ts);

	krm::RendererCommand::Clear();
	krm::RendererCommand::setClearColor({ 1.0f, 0.1f, 0.1f, 0.1f });

	krm::Renderer2D::beginScene(m_CameraController.GetCamera().GetViewProjectionMatrix());

	//TO DO z axis doesn't work. Need to fix blending
	krm::Renderer2D::submit({ 1.0f, 1.0f, 1.0f }, glm::vec2(4.0f), { 0.8f, 1.0f, 0.3f,1.0f }, 1.0f);
	krm::Renderer2D::submit({ 0.0f, 0.0f, 0.0f }, glm::vec2(2.0f), { 0.8f, 0.0f, 0.3f,1.0f }, 1.0f);

	krm::Renderer2D::endScene();
}

void ClientLayer::OnImGuiRender()
{
}

void ClientLayer::eventHandle(krm::Event& e)
{
	m_CameraController.eventHandle(e);
}




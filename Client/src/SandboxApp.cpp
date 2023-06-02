#include "SandboxApp.h"

ClientLayer::ClientLayer()
	: Layer("Example")
{
}

void ClientLayer::OnUpdate()
{
}

void ClientLayer::OnImGuiRender()
{
}

void ClientLayer::OnEvent(krm::Event& event)
{
}

SandboxApp::SandboxApp() { PushLayer(new ClientLayer); }

SandboxApp::~SandboxApp() {}

#pragma once
#include "KareeemEngine.h"

class ClientLayer : public krm::Layer
{
public:
	ClientLayer();

	void OnUpdate() override;

	virtual void OnImGuiRender() override;

	void OnEvent(krm::Event& event) override;


};

class SandboxApp : public krm::App
{
public:
	SandboxApp(krm::Window* window)
		: krm::App(window)
	{
		PushLayer(new ClientLayer); 
	}
	virtual ~SandboxApp() {}
};

krm::App* createApplication(krm::Window* window)
{
	return new SandboxApp(window);
}
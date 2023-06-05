#pragma once
#include "KareeemEngine.h"

class ClientLayer : public krm::Layer
{
public:
	ClientLayer();

	void OnUpdate(krm::TimeStep ts) override;
	virtual void OnImGuiRender() override;

	void eventHandle(krm::Event& e) override;

private:
	std::unique_ptr<krm::Shader> defaultShader;
	std::unique_ptr<krm::VertexArray> m_VertexArray;
	glm::vec3 position;

	krm::OrthographicCameraController m_CameraController;
	glm::mat4 model;
	float m_TranslationSpeed = 100;
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
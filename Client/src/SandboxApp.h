#pragma once
#include "KareeemEngine.h"

#include "imgui.h"
#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"

class ClientLayer : public krm::Layer
{
public:
	ClientLayer(GLFWwindow* window);

	void OnUpdate() override;

	virtual void OnImGuiRender() override;

	void OnEvent(krm::Event& event) override;

private:
	bool show_demo_window = true;
	bool show_another_window = false;
	ImVec4 clear_color;
};

class SandboxApp : public krm::App
{
public:
	SandboxApp();
	virtual ~SandboxApp();
};
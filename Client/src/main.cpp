#include "SandboxApp.h"

#include "imgui.h"

int MAIN
{
    krm::Log::Init();
    KRM_LOG_CLIENT_INFO("CLIENT SIDE LOGGING");
    SandboxApp app;
    app.run();
    return 0;
}
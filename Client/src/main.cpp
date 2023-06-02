#include "SandboxApp.h"

int MAIN
{
    krm::Log::Init();
    KRM_LOG_CLIENT_INFO("CLIENT SIDE LOGGING");
    krm::App app;
    app.run();
    return 0;
}
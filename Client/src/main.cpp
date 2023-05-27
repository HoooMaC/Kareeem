#include "KareeemEngine.h"
#include <GLFW\glfw3.h>

int MAIN
{
    krm::Log::Init();
    KRM_LOG_CLIENT_INFO("CLIENT SIDE LOGGING");
    krm::App app;
    app.run();
    int a = 10;
    return 0;
}
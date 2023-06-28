#include "Core/KRMpch.h"

#include "Core/Core.h"
#include "Core/Log.h"

#include "Core/App.h"

#include "OpenGL/Window.h"
#include "OpenGL/KRGLFW.h"
#include "OpenGL/OpenGLContext.h"

#include <GLEW/glew.h>

extern krm::App* createApplication(krm::Window* window);

int MAIN
{
    KRM_LOG_CLIENT_INFO("CLIENT SIDE LOGGING");

    krm::KRGLFW::init();

    krm::Window window = krm::Window(krm::WindowProps());

    if (glewInit() != GLEW_OK)
    {
        KRM_LOG_CORE_ERROR("Failed to Initialized GLEW");
        ASSERT(false);
        krm::OpenGLContext::destroyContext();
    }

    krm::App* app = createApplication(&window);

    //krm::KRImGui::init();

    app->run();

    delete app;

    krm::KRGLFW::shutdown();

    return 0;

}
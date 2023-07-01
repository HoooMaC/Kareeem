#include "Core/KRMpch.h"

#include "Core/Core.h"
#include "Core/Log.h"

#include "Core/App.h"

#include "OpenGL/Window.h"
#include "OpenGL/OpenGLContext.h"

#include <GLEW/glew.h>
#include <GLFW/glfw3.h>

extern krm::App* createApplication(krm::Window* window);

int MAIN
{
    krm::Window window = krm::Window(krm::WindowProps());

    krm::App* app = createApplication(&window);

    app->run();

    delete app;

    krm::OpenGLContext::destroyContext();
    glfwTerminate();

    return 0;

}
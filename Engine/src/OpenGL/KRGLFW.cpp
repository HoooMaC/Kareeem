#include "Core/KRMpch.h"

#include "KRGLFW.h"

#include "Core/Log.h"
#include "OpenGL/OpenGLContext.h"

#include <GLFW/glfw3.h>

namespace krm {

	int KRGLFW::m_majorVersion = 4;
	int KRGLFW::m_minorVersion = 5;
	int KRGLFW::m_Profile = GLFW_OPENGL_CORE_PROFILE;

	void KRGLFW::init(int majorV, int minorV, int profile)
	{
		if (!glfwInit())
		{
			glfwSetErrorCallback(errorCallback);
		}

		m_majorVersion = majorV;
		m_minorVersion = minorV;
		m_Profile = profile;

		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, m_majorVersion);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, m_minorVersion);

		glfwWindowHint(GLFW_OPENGL_PROFILE, m_Profile);
	}

	void KRGLFW::shutdown()
	{
		OpenGLContext::destroyContext();
		glfwTerminate();
	}

	void KRGLFW::errorCallback(int error, const char* message)
	{
		KRM_LOG_CORE_ERROR("Failed to Initialized GLFW");
		KRM_LOG_CORE_ERROR("GLFW Error : ({0}), ({1})", error, message);
	}

}
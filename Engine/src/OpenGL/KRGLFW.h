#pragma once

#define GLFW_OPENGL_ANY_PROFILE              0
#define GLFW_OPENGL_CORE_PROFILE    0x00032001
#define GLFW_OPENGL_COMPAT_PROFILE  0x00032002

namespace krm {

	class KRGLFW
	{
	public:
		static void init(int majorV = 4, int minorV = 5, int profile = GLFW_OPENGL_CORE_PROFILE);
		static void shutdown();
	private:
		static void errorCallback(int error, const char* message);
	private:
		static int m_majorVersion;
		static int m_minorVersion;
		static int m_Profile;
	};


}
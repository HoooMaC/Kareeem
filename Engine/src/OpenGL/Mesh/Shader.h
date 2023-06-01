#pragma once

#include "Core/KRMpch.h"
#include "Core/Core.h"

#include "OpenGL/Mesh/Buffer.h"

namespace krm {

	struct ShaderSource
	{
		std::string vertexShader;
		std::string fragmentShader;
	};

	class Shader : public OpenGL
	{
	public:
		Shader(const std::string& vertexFilepath, const std::string& fragmentFilepath);
		~Shader();

		void bind() const override;
		void unbind() const override;

	private:

		void makeShader(const std::string& vertexFilepath, const std::string& fragmentFilepath);
		ShaderSource readShader(const std::string& vertexFilepath, const std::string& fragmentFilepath);
		unsigned int compileShader(unsigned int type, const std::string& src);
		unsigned int createShader(const std::string& v_Shader, const std::string& f_Shader);

	private:
		std::string m_vertexFilePath, m_fragmentFilepath;

	};

}
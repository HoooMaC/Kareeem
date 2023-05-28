#pragma once
#include "Core\KRMpch.h"
#include "OpenGL\glInterface.h"

#include "glm.hpp"
#include "gtc\matrix_transform.hpp"

namespace krm {

	struct ShaderSource
	{
		std::string vertexShader;
		std::string fragmentShader;
	};

	class Shader : public OpenGL
	{
	private:
		std::string m_vertexFilePath, m_fragmentFilepath;
		std::unordered_map<std::string, int> m_Uniform;

	public:
		Shader(const std::string& vertexFilepath, const std::string& fragmentFilepath);
		Shader();
		~Shader();

		void makeShader(const std::string& vertexFilepath, const std::string& fragmentFilepath);
		void uniform1i(const std::string& variable, int i);
		void uniform4f(const std::string& variable, float f1, float f2, float f3, float f4);
		void uniformMat4f(const std::string& variable, const glm::mat4& matrix);
		void uniform1iv(const std::string& variable, const int count, const int* value);

		void bind() const override;
		void unbind() const override;

	private:
		ShaderSource readShader(const std::string& vertexFilepath, const std::string& fragmentFilepath);
		unsigned int compileShader(unsigned int type, const std::string& src);
		unsigned int createShader(const std::string& v_Shader, const std::string& f_Shader);

		int getUniformLocation(const std::string& name);
	};

}
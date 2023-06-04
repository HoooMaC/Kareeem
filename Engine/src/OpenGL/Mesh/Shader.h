#pragma once

#include "Core/KRMpch.h"
#include "Core/Core.h"

#include "OpenGL/Mesh/Buffer.h"

#include <GLEW/glew.h>
namespace krm {

	enum class UniformType : uint8_t
	{
		NONE = 0, Float, Float2, Float3, Float4, Mat2f, Mat3f, Mat4f
	};

	struct UniformData
	{
		GLenum m_type;
		int m_count;
		int m_location;
		const void* m_data;

		UniformData(GLenum type, int count)
			: m_type(type), m_count(count), m_location(-1), m_data(nullptr)
		{
		}
		UniformData()
			: m_type(0), m_count(1), m_location(-1), m_data(nullptr)
		{
		}

		UniformData(const UniformData& other)
			: m_type(other.m_type), m_count(other.m_count), m_location(other.m_location), m_data(other.m_data)
		{
		}

	};

	class Shader : public OpenGL
	{
	private:

	public:
		Shader(const std::string& vertexFilepath, const std::string& fragmentFilepath);
		~Shader();

		void bind() const override;
		void unbind() const override;

		void bindAndUploadUniform() const;

		void uploadUniform(const char* variable, const void* data);

	private:

		int getUniformLoc(const std::string& variable);

		void makeShader(const std::string& vertexFilepath, const std::string& fragmentFilepath);
		std::pair<std::string, std::string> readShader(const std::string& vertexFilepath, const std::string& fragmentFilepath);
		unsigned int compileShader(unsigned int type, const std::string& src);
		unsigned int createShader(const std::string& v_Shader, const std::string& f_Shader);

	private:
		std::string m_vertexFilePath, m_fragmentFilepath;
		std::unordered_map<std::string, UniformData> m_UniformList;
	};

}
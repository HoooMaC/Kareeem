#pragma once

#include "Core/KRMpch.h"
#include "Core/Core.h"

#include "OpenGL/Mesh/Buffer.h"

namespace krm {

	enum class UniformType : uint8_t
	{
		NONE = 0, Float, Float2, Float3, Float4, Mat2f, Mat3f, Mat4f
	};

	class Shader : public OpenGL
	{
	private:
		struct UniformData
		{
			std::string name;
			UniformType type;
			uint8_t count;
			int location;
			const void* data;

			bool operator==(std::string other)
			{
				return name == other;
			}
		};
	public:
		Shader(const std::string& vertexFilepath, const std::string& fragmentFilepath);
		~Shader();

		void bind() const override;
		void unbind() const override;

		void bindAndUploadUniform() const;
		void uploadUniform(UniformData uniform) const;

		void addNewUniform(const std::string& variable, UniformType type, uint8_t count, const void* data);

	private:

		int getUniformLoc(const std::string& variable);

		void makeShader(const std::string& vertexFilepath, const std::string& fragmentFilepath);
		std::pair<std::string, std::string> readShader(const std::string& vertexFilepath, const std::string& fragmentFilepath);
		unsigned int compileShader(unsigned int type, const std::string& src);
		unsigned int createShader(const std::string& v_Shader, const std::string& f_Shader);

	private:
		std::string m_vertexFilePath, m_fragmentFilepath;
		std::vector<UniformData> m_UniformList;
	};

}
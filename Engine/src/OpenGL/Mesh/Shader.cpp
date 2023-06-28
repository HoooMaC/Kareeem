#include "Core/KRMpch.h"

#include "Shader.h"

#include "Core/Log.h"

#include "OpenGL/Mesh/MeshLog.h"

#include <GLEW/glew.h>

namespace krm {

	Shader::Shader(const std::string& vertexFilepath, const std::string& fragmentFilepath)
		: m_vertexFilePath(vertexFilepath), m_fragmentFilepath(fragmentFilepath)
	{
		makeShader(vertexFilepath, fragmentFilepath);

		int num_uniforms, maxUniformLength;
		glGetProgramiv(m_RendererID, GL_ACTIVE_UNIFORMS, &num_uniforms);
		glGetProgramiv(m_RendererID, GL_ACTIVE_UNIFORM_MAX_LENGTH, &maxUniformLength);

		for (int i = 0; i < num_uniforms; i++)
		{
			GLchar* name = new char[maxUniformLength];
			GLenum type;
			int count;
			GLsizei length;
			glGetActiveUniform(m_RendererID, i, maxUniformLength * sizeof(char), &length, &count, &type, name);

			m_UniformList[name] = UniformData(type, count);
		}
	}

	Shader::~Shader()

	{
		glDeleteProgram(m_RendererID);
		KRM_INFO_MESSAGE("Shader has with Id : {} been deleted", m_RendererID);
	}

	void Shader::bind() const
	{
		glUseProgram(m_RendererID);

		KRM_INFO_MESSAGE("Shader with Id : {} has been bound", m_RendererID);
	}

	void Shader::unbind() const
	{
		glUseProgram(0);
		KRM_INFO_MESSAGE("Shader with Id : {} has been unbound", m_RendererID);
	}

	void Shader::bindAndUploadUniform() const
	{
		glUseProgram(m_RendererID);

		//int countUniform = 0;
		//for (auto& uniform : m_UniformList)
		//{
		//	uploadUniform(uniform);
		//	countUniform++;
		//}

		//KRM_INFO_MESSAGE("Shader with Id : {} has been bound and {1} uniform has been uploaded", m_RendererID, countUniform);
	}

	//need to change this function name
	void Shader::uploadUniform(const char* variable, const void* data)
	{
		//must fixed, if uniform is an array
		std::string target = variable;
		//if (m_UniformList[target].m_count > 1)
		//{
		//	if (target.find("[0]") == std::string::npos)
		//	{
		//		target.append("[0]");
		//	}
		//}

		if (m_UniformList.find(target) == m_UniformList.end())
		{
			if (m_UniformList.find(target + "[0]") == m_UniformList.end())
			{
				KRM_LOG_CORE_ERROR("Variable not found");
				ASSERT(false);
				return;
			}
			target.append("[0]");
		}


		m_UniformList[target].m_location = glGetUniformLocation(m_RendererID, target.c_str());
		m_UniformList[target].m_data = data;

		switch (m_UniformList[target].m_type)
		{
		case GL_BOOL	   : return glUniform1iv(m_UniformList[target].m_location, m_UniformList[target].m_count, (const int*)m_UniformList[target].m_data); 
		case GL_INT		   : return glUniform1iv(m_UniformList[target].m_location, m_UniformList[target].m_count, (const int*)m_UniformList[target].m_data); 
		case GL_SAMPLER_2D : return glUniform1iv(m_UniformList[target].m_location, m_UniformList[target].m_count, (const int*)m_UniformList[target].m_data);
		case GL_INT_VEC2   : return glUniform2iv(m_UniformList[target].m_location, m_UniformList[target].m_count, (const int*)m_UniformList[target].m_data); 
		case GL_INT_VEC3   : return glUniform3iv(m_UniformList[target].m_location, m_UniformList[target].m_count, (const int*)m_UniformList[target].m_data); 
		case GL_INT_VEC4   : return glUniform4iv(m_UniformList[target].m_location, m_UniformList[target].m_count, (const int*)m_UniformList[target].m_data); 
		case GL_FLOAT	   : return glUniform1fv(m_UniformList[target].m_location, m_UniformList[target].m_count, (const float*)m_UniformList[target].m_data); 
		case GL_FLOAT_VEC2 : return glUniform2fv(m_UniformList[target].m_location, m_UniformList[target].m_count, (const float*)m_UniformList[target].m_data); 
		case GL_FLOAT_VEC3 : return glUniform3fv(m_UniformList[target].m_location, m_UniformList[target].m_count, (const float*)m_UniformList[target].m_data); 
		case GL_FLOAT_VEC4 : return glUniform4fv(m_UniformList[target].m_location, m_UniformList[target].m_count, (const float*)m_UniformList[target].m_data); 
		case GL_FLOAT_MAT2 : return glUniformMatrix2fv(m_UniformList[target].m_location, m_UniformList[target].m_count, GL_FALSE, (const float*)m_UniformList[target].m_data); 
		case GL_FLOAT_MAT3 : return glUniformMatrix3fv(m_UniformList[target].m_location, m_UniformList[target].m_count, GL_FALSE, (const float*)m_UniformList[target].m_data); 
		case GL_FLOAT_MAT4 : return glUniformMatrix4fv(m_UniformList[target].m_location, m_UniformList[target].m_count, GL_FALSE, (const float*)m_UniformList[target].m_data); 
		}
		KRM_LOG_CORE_ERROR("Uniform {} Type unknown", target);

		ASSERT(false);
		return;
	}


	int Shader::getUniformLoc(const std::string& variable)
	{
		int location = glGetUniformLocation(m_RendererID, variable.c_str());
		if(location != -1)
			return location;
		else
		{
			KRM_LOG_CORE_ERROR("Uniform Name Doesn't Exist");
			ASSERT(false);
		}
		return location;
	}

	void Shader::makeShader(const std::string& vertexFilepath, const std::string& fragmentFilepath)
	{
		m_vertexFilePath = vertexFilepath;
		m_fragmentFilepath = fragmentFilepath;

		auto[vertexSrc, fragmentSrc] = readShader(vertexFilepath, fragmentFilepath);

		m_RendererID = createShader(vertexSrc, fragmentSrc);
		bind();
	}

	std::pair<std::string, std::string> Shader::readShader(const std::string& vertexFilepath, const std::string& fragmentFilepath)
	{
		std::ifstream vertexStream(vertexFilepath);
		if (!vertexStream.is_open())
		{
			ASSERT(false);
		}
		std::stringstream ss[2];

		std::string line;
		while (getline(vertexStream, line))
		{
			ss[0] << line << '\n';
		}

		std::ifstream fragmentStream(fragmentFilepath);
		if (!fragmentStream.is_open())
		{
			ASSERT(false);
		}
		while (getline(fragmentStream, line))
		{
			ss[1] << line << '\n';
		}

		return { ss[0].str(), ss[1].str() };
	}

	unsigned int Shader::compileShader(unsigned int type, const std::string& src)
	{
		unsigned int id = glCreateShader(type);
		const char* source = src.c_str();

		glShaderSource(id, 1, &source, nullptr);
		glCompileShader(id);

		int result;
		glGetShaderiv(id, GL_COMPILE_STATUS, &result);
		if (result == GL_FALSE)
		{
			int length;
			glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);

			char* message = new char[length];
			glGetShaderInfoLog(id, length, &length, message);


			const char* shadertype = (type == GL_VERTEX_SHADER ? "vertex" : "fragment");
			KRM_LOG_CORE_ERROR("Failed to compile [{}] shader", shadertype);
			KRM_LOG_CORE_ERROR("{}", message);
			delete[] message;
			glDeleteShader(id);
			return 0;
		}

		return id;
	}

	unsigned int Shader::createShader(const std::string& v_Shader, const std::string& f_Shader)
	{
		unsigned int program = glCreateProgram();
		unsigned int vs = compileShader(GL_VERTEX_SHADER, v_Shader);
		unsigned int fs = compileShader(GL_FRAGMENT_SHADER, f_Shader);

		glAttachShader(program, vs);
		glAttachShader(program, fs);

		glLinkProgram(program);
		glValidateProgram(program);

		glDeleteShader(vs);
		glDeleteShader(fs);

		KRM_INFO_MESSAGE("Shader program has been created succesfully with Id : {}", program);

		return program;
	}

}
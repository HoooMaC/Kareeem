#include "Core\KRMpch.h"
#include "GLEW\glew.h"

#include "Shader.h"
#include "Core\Log.h"

namespace krm {

	Shader::Shader(const std::string& vertexFilepath, const std::string& fragmentFilepath)
		: m_vertexFilePath(vertexFilepath), m_fragmentFilepath(fragmentFilepath)
	{
		makeShader(vertexFilepath, fragmentFilepath);
	}

	Shader::Shader()
		: m_vertexFilePath(""), m_fragmentFilepath("")
	{

	}

	Shader::~Shader()

	{
		(glDeleteProgram(m_RendererID));
		KRM_LOG_CORE_INFO("Shader has with Id : {0} been deleted", m_RendererID);
	}

	void Shader::makeShader(const std::string& vertexFilepath, const std::string& fragmentFilepath)
	{
		m_vertexFilePath = vertexFilepath;
		m_fragmentFilepath = fragmentFilepath;

		ShaderSource source = readShader(vertexFilepath, fragmentFilepath);

		m_RendererID = createShader(source.vertexShader, source.fragmentShader);
		bind();
	}

	void Shader::uniform4f(const std::string& variable, float f1, float f2, float f3, float f4)
	{
		(glUniform4f(getUniformLocation(variable), f1, f2, f3, f4));
	}

	void Shader::uniformMat4f(const std::string& variable, const glm::mat4& matrix)
	{
		(glUniformMatrix4fv(getUniformLocation(variable), 1, GL_FALSE, &matrix[0][0]));
		//(glUniformMatrix4fv(getUniformLocation(variable), 1, GL_FALSE, &matrix[0][0]));
	}

	void Shader::uniform1iv(const std::string& variable, const int count, const int* value)
	{
		int loc = getUniformLocation(variable);
		(glUniform1iv(loc, count, value));
	}

	void Shader::uniform1i(const std::string& variable, int i)
	{
		int loc = getUniformLocation(variable);
		glUniform1i(loc, i);
	}

	void Shader::bind() const
	{
		(glUseProgram(m_RendererID));
		KRM_LOG_CORE_INFO("Shader with Id : {0} has been bound", m_RendererID);
	}

	void Shader::unbind() const
	{
		(glUseProgram(0));
		KRM_LOG_CORE_INFO("Shader with Id : {0} has been unbound", m_RendererID);
	}

	ShaderSource Shader::readShader(const std::string& vertexFilepath, const std::string& fragmentFilepath)
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
		(unsigned int id = glCreateShader(type));
		const char* source = src.c_str();

		(glShaderSource(id, 1, &source, nullptr));
		(glCompileShader(id));

		int result;
		glGetShaderiv(id, GL_COMPILE_STATUS, &result);
		if (result == GL_FALSE)
		{
			int length;
			glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);

			char* message = new char[length];
			glGetShaderInfoLog(id, length, &length, message);


			const char* shadertype = (type == GL_VERTEX_SHADER ? "vertex" : "fragment");
			LOG_ERROR("Failed to compile [{0}] shader", shadertype);
			/*std::cout << "Failed to compile "
				<< (type == GL_VERTEX_SHADER ? "vertex " : "fragment ") << "shader\n" << message << "\n";*/

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

		(glAttachShader(program, vs));
		(glAttachShader(program, fs));

		(glLinkProgram(program));
		(glValidateProgram(program));

		(glDeleteShader(vs));
		(glDeleteShader(fs));

		KRM_LOG_CORE_INFO("Shader program has been created succesfully with Id : {0}", program);

		return program;
	}

	int Shader::getUniformLocation(const std::string& name)
	{
		if (m_Uniform.find(name) != m_Uniform.end())
		{
			return m_Uniform[name];
		}

		(int location = glGetUniformLocation(m_RendererID, name.c_str()));

		if (location == -1)
		{
			LOG_ERROR("Warning : uniform {0} doesn't exist", name);
		}

		m_Uniform[name] = location;
		return location;
	}

}
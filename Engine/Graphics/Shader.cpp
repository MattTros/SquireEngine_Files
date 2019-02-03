#include "Shader.h"


std::unique_ptr<Shader> Shader::shaderInstance = nullptr;
std::map<std::string, GLuint> Shader::programs = std::map<std::string, GLuint>();

Shader::Shader()
{
}


Shader::~Shader()
{
	if (programs.size() > 0)
	{
		for (auto entry : programs)
		{
			glDeleteProgram(entry.second);
		}
		programs.clear();
	}
}

Shader* Shader::GetInstance()
{
	if (shaderInstance.get() == nullptr)
	{
		shaderInstance.reset(new Shader);
	}
	return shaderInstance.get();
}

void Shader::CreateProgram(const std::string& shaderName_, const std::string& vertexShaderName_, const std::string& fragmentShaderName_)
{
	std::string vertexShaderCode = ReadShader(vertexShaderName_);
	std::string fragmentShaderCode = ReadShader(fragmentShaderName_);

	GLuint vertexShader = CreateShader(GL_VERTEX_SHADER, vertexShaderCode, vertexShaderName_);
	GLuint fragmentShader = CreateShader(GL_FRAGMENT_SHADER, fragmentShaderCode, fragmentShaderName_);

	GLint linkResult = 0;
	GLuint program = glCreateProgram();
	glAttachShader(program, vertexShader);
	glAttachShader(program, fragmentShader);
	glLinkProgram(program);
	glGetProgramiv(program, GL_LINK_STATUS, &linkResult);
	if (!linkResult)
	{
		GLint infoLogLength = 0;
		glGetProgramiv(program, GL_INFO_LOG_LENGTH, &infoLogLength);
		char programInfo[512];
		glGetProgramInfoLog(program, infoLogLength, NULL, &programInfo[0]);
		Debug::Error("Shader linker: Link error: " + shaderName_ + "\n" + programInfo, __FILE__, __LINE__);
		return;
	}
	programs[shaderName_] = program;
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}

const GLuint Shader::GetShader(const std::string& shaderName_)
{
	if (programs.find(shaderName_) != programs.end())
	{
		return programs[shaderName_];
	}
	return -1;
}

std::string Shader::ReadShader(const std::string& fileName_)
{
	std::string shaderCode;
	std::ifstream file;
	file.exceptions(std::ifstream::badbit);
	try
	{
		file.open(fileName_);
		std::stringstream tempStream;
		tempStream << file.rdbuf();
		file.close();
		shaderCode = tempStream.str();
	}
	catch (std::ifstream::failure error_)
	{
		Debug::Error("Could not read shader file", __FILE__, __LINE__);
		return "";
	}
	return shaderCode;
}

GLuint Shader::CreateShader(GLenum shaderType_, const std::string source_, const std::string& shaderName_)
{
	GLint compile_result = 0;
	GLuint shader = glCreateShader(shaderType_);
	const char* shaderCodePtr = source_.c_str();
	const int shaderCodeSize = source_.size();
	glShaderSource(shader, 1, &shaderCodePtr, &shaderCodeSize);
	glCompileShader(shader);
	glGetShaderiv(shader, GL_COMPILE_STATUS, &compile_result);
	if (!compile_result)
	{
		GLint infoLogLength = 0;
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLogLength);
		char shaderLog[512];
		glGetShaderInfoLog(shader, infoLogLength, NULL, &shaderLog[0]);
		Debug::Error("Error compiling shader " + shaderName_ +"\n" + shaderLog, __FILE__, __LINE__);
		return 0;
	}
	return shader;
}

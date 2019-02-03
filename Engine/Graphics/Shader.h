#ifndef SHADER_H
#define SHADER_H

#include <fstream>
#include <iostream>
#include <sstream>
#include <map>
#include <vector>
#include <memory>
#include <glew.h>
#include "../Core/Debug.h"

class Shader
{
public:
	Shader(const Shader&) = delete;
	Shader(Shader&&) = delete;
	Shader& operator = (const Shader&) = delete;
	Shader& operator = (Shader&&) = delete;

	static Shader * GetInstance();
	void CreateProgram(const std::string& shaderName_, const std::string& vertexShaderName_, const std::string& fragmentShaderName_);
	static const GLuint GetShader(const std::string& shaderName_);
private: 
	Shader();
	~Shader();

	static std::unique_ptr<Shader> shaderInstance;
	friend std::default_delete<Shader>;

	std::string ReadShader(const std::string& fileName_);
	GLuint CreateShader(GLenum shaderType_, const std::string source_, const std::string& shaderName_);
	static std::map<std::string, GLuint> programs;
};

#endif // !SHADER_H


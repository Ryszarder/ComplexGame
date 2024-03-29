#include "ShaderProgram.h"
#include "Utilities.h"
#include <iostream>

ShaderProgram::ShaderProgram(std::string vertexFilename, std::string geometryFilename, std::string fragmentFilename)
{
	everythingIsOkay = true;

	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	geometryShader = glCreateShader(GL_GEOMETRY_SHADER);
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

	
	shaderProgram = glCreateProgram();
	
	std::string vertexSource = LoadFileAsString(vertexFilename);
	std::string geometrySource = LoadFileAsString(geometryFilename);
	std::string fragmentSource = LoadFileAsString(fragmentFilename);
	
	const char* vertexSourceC = vertexSource.c_str();

	glShaderSource(vertexShader, 1, &vertexSourceC, nullptr);
	glCompileShader(vertexShader);

	GLchar errorLog[512];
	GLint success = 0;
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (success == GL_FALSE)
	{
		//Something failed with the vertex shader compilation
		std::cout << "Vertex shader " << vertexFilename << " failed because..." << std::endl;
		glGetShaderInfoLog(vertexShader, 512, nullptr, errorLog);
		std::cout << errorLog << std::endl;
		everythingIsOkay = false;
	}
	else
	{
		std::cout << "Everything is okay (with the vertex shader at least)" << std::endl;
	}

	const char* geometrySourceC = geometrySource.c_str();

	glShaderSource(geometryShader, 1, &geometrySourceC, nullptr);
	glCompileShader(geometryShader);

	glGetShaderiv(geometryShader, GL_COMPILE_STATUS, &success);
	if (success == GL_FALSE)
	{
		//Something failed with the fragment shader compilation
		std::cout << "Geometry shader " << geometryFilename << " failed because..." << std::endl;
		glGetShaderInfoLog(geometryShader, 512, nullptr, errorLog);
		std::cout << errorLog << std::endl;
		everythingIsOkay = false;
	}
	else
	{
		std::cout << "Everything is okay (with the geometry shader at least)" << std::endl;
	}

	const char* fragmentSourceC = fragmentSource.c_str();

	glShaderSource(fragmentShader, 1, &fragmentSourceC, nullptr);
	glCompileShader(fragmentShader);

	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	if (success == GL_FALSE)
	{
		//Something failed with the fragment shader compilation
		std::cout << "Fragment shader " << fragmentFilename << " failed because..." << std::endl;
		glGetShaderInfoLog(fragmentShader, 512, nullptr, errorLog);
		std::cout << errorLog << std::endl;
		everythingIsOkay = false;
	}
	else
	{
		std::cout << "Everything is okay (with the fragment shader at least)" << std::endl;
	}

	glAttachShader(shaderProgram, fragmentShader);
	glAttachShader(shaderProgram, geometryShader);
	glAttachShader(shaderProgram, vertexShader);
	glLinkProgram(shaderProgram);
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	if (success == GL_FALSE)
	{
		std::cout << "The linking is busted or something" << std::endl;
		glGetProgramInfoLog(shaderProgram, 512, nullptr, errorLog);
		std::cout << errorLog << std::endl;
		everythingIsOkay = false;
	}

	if (everythingIsOkay)
	{
		std::cout << "It appears that things are pretty okay" << std::endl;
	}

	glDeleteShader(vertexShader);
	glDeleteShader(geometryShader);
	glDeleteShader(fragmentShader);
}

ShaderProgram::ShaderProgram(std::string computeFilename)
{
	everythingIsOkay = true;
	computeShader = glCreateShader(GL_COMPUTE_SHADER);

	std::string computeSource = LoadFileAsString(computeFilename);

	shaderProgram = glCreateProgram();

	const char* computeSourceC = computeSource.c_str();

	glShaderSource(computeShader, 1, &computeSourceC, nullptr);
	glCompileShader(computeShader);

	GLchar errorLog[512];
	GLint success = 0;
	glGetShaderiv(computeShader, GL_COMPILE_STATUS, &success);
	if (success == GL_FALSE)
	{
		//Something failed with the compute shader compilation
		std::cout << "Compute shader " << computeFilename << " failed becuase..." << std::endl;
		glGetShaderInfoLog(computeShader, 512, nullptr, errorLog);
		std::cout << errorLog << std::endl;
		everythingIsOkay = false;
	}
	else
	{
		std::cout << "Everything is okay (with the compute shader at least)" << std::endl;
	}

	glAttachShader(shaderProgram, computeShader);
	glLinkProgram(shaderProgram);
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	if (success == GL_FALSE)
	{
		std::cout << "The linking is busted or something" << std::endl;
		glGetProgramInfoLog(shaderProgram, 512, nullptr, errorLog);
		std::cout << errorLog << std::endl;
		everythingIsOkay = false;
	}

	if (everythingIsOkay)
	{
		std::cout << "It appears that things are pretty okay" << std::endl;
	}

	glDeleteShader(computeShader);
}

ShaderProgram::~ShaderProgram()
{
	glDeleteProgram(shaderProgram);
}


void ShaderProgram::UseShader()
{
	glUseProgram(shaderProgram);
}

GLuint ShaderProgram::GetUniformLocation(std::string varName)
{
	return glGetUniformLocation(shaderProgram, varName.c_str());
}

void ShaderProgram::SetUniform(std::string varName, float value)
{
	GLuint varLoc = glGetUniformLocation(shaderProgram, varName.c_str());
	UseShader();
	glUniform1f(varLoc, value);
}

void ShaderProgram::SetUniform(std::string varName, int value)
{
	GLuint varLoc = glGetUniformLocation(shaderProgram, varName.c_str());
	UseShader();
	glUniform1i(varLoc, value);
}

void ShaderProgram::SetUniform(std::string varName, glm::vec3 value)
{
	GLuint varLoc = glGetUniformLocation(shaderProgram, varName.c_str());
	UseShader();
	glUniform3f(varLoc, value.x, value.y, value.z);
}

void ShaderProgram::SetUniform(std::string varName, glm::mat4 value)
{
	GLuint varLoc = glGetUniformLocation(shaderProgram, varName.c_str());
	UseShader();
	glUniformMatrix4fv(varLoc, 1, GL_FALSE, &value[0][0]);
}

void ShaderProgram::ClearPrograms()
{
	glUseProgram(0);
}
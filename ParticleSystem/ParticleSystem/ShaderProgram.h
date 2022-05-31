#pragma once

#include "Graphics.h"
#include "glm.hpp"
#include <string>

class ShaderProgram
{
private:
	//Remember, OpenGL manages its resources itself and gives you handles to them.
	//That's what all this 'GLuint' business is about.
	GLuint shaderProgram;
	GLuint vertexShader;
	GLuint fragmentShader;
	GLuint computeProgram;
	GLuint computeShader;

	bool everythingIsOkay = false;

public:
	ShaderProgram() {}
	ShaderProgram(std::string vertexFilename, std::string fragmentFilename);
	ShaderProgram(std::string computeFilename);

	~ShaderProgram() {}	//TODO this should free the resources of shader.

	bool IsEverythingOkay() const { return everythingIsOkay; }

	void UseShaderVertFrag();

	void UseShaderComp();

	GLuint GetUniformLocation(std::string varName);

	void SetUniform(std::string varName, float value);
	void SetUniform(std::string varName, int value);
	void SetUniform(std::string varName, glm::vec3 value);
	void SetUniform(std::string varName, glm::mat4 value);
};
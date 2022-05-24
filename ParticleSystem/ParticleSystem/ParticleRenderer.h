#pragma once

#include "Graphics.h"

class ShaderProgram;

class ParticleRenderer
{
public:
	ParticleRenderer();
	~ParticleRenderer();

	//void Update(ShaderProgram particleShader);

	void Draw(ShaderProgram particleShader);

private:
	GLuint particleVAO;
};


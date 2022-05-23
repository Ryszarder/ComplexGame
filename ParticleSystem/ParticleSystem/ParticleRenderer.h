#pragma once

#include "Graphics.h"

class ShaderProgram;

class ParticleRenderer
{
public:
	ParticleRenderer();
	~ParticleRenderer();

	void Draw(ShaderProgram particleShader);

	void Update();

private:
	GLuint particleVAO;
};


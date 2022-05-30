#pragma once

#include "Graphics.h"
#include "Particle.h"

class ShaderProgram;

class ParticleRenderer
{
public:
	ParticleRenderer();
	~ParticleRenderer();

	void Update(ShaderProgram particleShader);

	void Draw(ShaderProgram particleShader, ShaderProgram vertFragShader);

	std::vector<Particle> m_Vparticles;

private:
	GLuint particleVAO;
};


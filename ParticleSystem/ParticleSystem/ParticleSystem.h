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

	void Draw(ShaderProgram vertFragShader);

	std::vector<Particle> m_Vparticles;

private:
	GLuint particleVAO;
	double lastTime = 0.0f;
	double currentTime = 0.0f;
	float deltaTime = 0.0f;

};


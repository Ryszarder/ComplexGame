#pragma once

#include "Graphics.h"
#include "Particle.h"
#include "Texture.h"

class ShaderProgram;

class ParticleSystem
{
public:
	ParticleSystem();
	~ParticleSystem();

	void Update(ShaderProgram particleShader);

	void Draw(ShaderProgram vertFragShader);

	std::vector<Particle> m_Vparticles;

private:
	GLuint particleVAO;
	Texture* m_Tsmoke;
	Texture* m_Tfire;

	double lastTime = 0.0f;
	float deltaTime = 0.0f;
};
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

	//GLuint particleVAO;
	//Texture* particleTexture;
	//ShaderProgram* m_shader;
	double lastTime = 0.0f;
	double currentTime = 0.0f;
	float deltaTime = 0.0f;
};
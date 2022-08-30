#pragma once
#include "Particle.h"
#include "Texture.h"

class ShaderProgram;

class ParticleSystem
{
public:
	ParticleSystem();
	~ParticleSystem();

	void Update(ShaderProgram& particleShader);

	void Draw(ShaderProgram& vertFragShader);

	void ParticleTexture(std::string partTexure);

	ParticleSystem& operator=(const ParticleSystem& other) = delete;
	ParticleSystem(const ParticleSystem& other) = delete;

	std::vector<Particle> m_Vparticles;

private:
	GLuint particleVAO;
	Texture* m_Ttexture;

	double lastTime = 0.0f;
	float deltaTime = 0.0f;
};
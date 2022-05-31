#include "ParticleRenderer.h"
#include "Graphics.h"
#include "ShaderProgram.h"

#include "ext/matrix_transform.hpp"
#include "ext/matrix_clip_space.hpp"

#include <random>
#include <time.h>   

#define NUM_PARTICLES 1024 * 1024
#define WORK_GROUP_SIZE 128
#define MAX_PARTICLES 16384

ParticleRenderer::ParticleRenderer()
{
	double lastTime = glfwGetTime();
	srand((unsigned)time(NULL));

	glGenBuffers(1, &particleVAO);

	for (int i = 0; i < MAX_PARTICLES; i++)
	{
		Particle thisParticle;

		thisParticle.position.x = ((float)rand() / (float)(RAND_MAX)) * (0.5f - -0.5f) + -0.5f;
		thisParticle.position.y = ((float)rand() / (float)(RAND_MAX)) * (0.5f - -0.5f) + -0.5f;
		thisParticle.position.z = ((float)rand() / (float)(RAND_MAX)) * (0.5f - -0.5f) + -0.5f;;
		thisParticle.position.w = 1.0f;

		thisParticle.velocity.x = ((float)rand() / (float)(RAND_MAX)) * (0.5f - -0.5f) + -0.5f;
		thisParticle.velocity.y = ((float)rand() / (float)(RAND_MAX)) * (0.5f - -0.5f) + -0.5f;
		thisParticle.velocity.z = ((float)rand() / (float)(RAND_MAX)) * (0.5f - -0.5f) + -0.5f;;
		thisParticle.velocity.w = 1.0f;

		thisParticle.colour.x = (float)rand() / (float)RAND_MAX;
		thisParticle.colour.y = (float)rand() / (float)RAND_MAX;
		thisParticle.colour.z = (float)rand() / (float)RAND_MAX;
		thisParticle.colour.w = 1.0f;

		m_Vparticles.push_back(thisParticle);
	};

	glBindBuffer(GL_SHADER_STORAGE_BUFFER, particleVAO);
	glBufferData(GL_SHADER_STORAGE_BUFFER, sizeof(Particle) * m_Vparticles.size(), m_Vparticles.data(), GL_STATIC_DRAW);
	glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 0, particleVAO);

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);
	//glEnableVertexAttribArray(3);
}

ParticleRenderer::~ParticleRenderer()
{
}

void ParticleRenderer::Update(ShaderProgram particleShader)
{
	glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 0, particleVAO);

	currentTime = glfwGetTime();
	deltaTime = float(currentTime - lastTime);
	lastTime = currentTime;

	particleShader.SetUniform("deltaTime", deltaTime);

	particleShader.UseShader();
	glDispatchCompute(MAX_PARTICLES / WORK_GROUP_SIZE, 1, 1);
	glMemoryBarrier(GL_SHADER_STORAGE_BARRIER_BIT);
}

void ParticleRenderer::Draw(ShaderProgram vertFragShader)
{
	vertFragShader.UseShader();
	glBindBuffer(GL_ARRAY_BUFFER, particleVAO);

	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(Particle), (void*)offsetof(Particle, position));
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(Particle), (void*)offsetof(Particle, velocity));
	glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, sizeof(Particle), (void*)offsetof(Particle, colour));
	//glVertexAttribPointer(3, 1, GL_FLOAT, GL_FALSE, sizeof(Particle), (void*)offsetof(Particle, age));

	glPointSize(5);

	glDrawArrays(GL_POINTS, 0, MAX_PARTICLES);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

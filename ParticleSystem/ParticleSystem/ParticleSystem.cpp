#include "ParticleSystem.h"
#include "Graphics.h"
#include "ShaderProgram.h"

#include "ext/matrix_transform.hpp"
#include "ext/matrix_clip_space.hpp"

#include <random>
#include <time.h>   

#define WORK_GROUP_SIZE 128
#define MAX_PARTICLES 16384

ParticleSystem::ParticleSystem()
{
	srand((unsigned)time(NULL));


	glGenBuffers(1, &particleVAO);

	for (int i = 0; i < MAX_PARTICLES; i++)
	{
		Particle thisParticle;

		thisParticle.position.x = ((float)rand() / (float)(RAND_MAX)) + -0.5f;
		thisParticle.position.y = ((float)rand() / (float)(RAND_MAX)) + -0.5f;
		thisParticle.position.z = ((float)rand() / (float)(RAND_MAX)) + -0.5f;
		thisParticle.position.w = 1.0f;

		thisParticle.velocity.x = ((float)rand() / (float)(RAND_MAX)) + -0.5f;
		thisParticle.velocity.y = ((float)rand() / (float)(RAND_MAX)) + -0.5f;
		thisParticle.velocity.z = ((float)rand() / (float)(RAND_MAX)) + -0.5f;
		thisParticle.velocity.w = 1.0f;

		thisParticle.colour.x = 1.0f;
		thisParticle.colour.y = 1.0f;
		thisParticle.colour.z = 1.0f;
		thisParticle.colour.w = 1.0f;

		thisParticle.alphaAge.x = 1.0f;
		thisParticle.alphaAge.y = ((float)rand() / (float)(RAND_MAX)) + 1.0f;
		thisParticle.alphaAge.z = ((float)rand() / (float)(RAND_MAX)) + 1.0f;
		thisParticle.alphaAge.w = 1.0f;

		thisParticle.newVelocity.x = ((float)rand() / (float)(RAND_MAX)) + -0.5f;
		thisParticle.newVelocity.y = ((float)rand() / (float)(RAND_MAX));
		thisParticle.newVelocity.z = ((float)rand() / (float)(RAND_MAX)) + -0.5f;
		thisParticle.newVelocity.w = 1.0f;

		m_Vparticles.push_back(thisParticle);
	};

	glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 0, particleVAO);
	glBufferData(GL_SHADER_STORAGE_BUFFER, sizeof(Particle) * m_Vparticles.size(), m_Vparticles.data(), GL_STATIC_DRAW);
	glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0);

	m_Tsmoke = new Texture("Texture/particle3.png");
	m_Tfire = new Texture("Texture/Fire.png");
}

ParticleSystem::~ParticleSystem()
{
}

void ParticleSystem::Update(ShaderProgram particleShader)
{
	srand((unsigned)time(NULL));
	glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 0, particleVAO);

	double currentTime = glfwGetTime();
	deltaTime = (float)(currentTime - lastTime);
	lastTime = currentTime;

	particleShader.UseShader();

	particleShader.SetUniform("deltaTime", deltaTime);

	glDispatchCompute(MAX_PARTICLES / WORK_GROUP_SIZE, 1, 1);
	glMemoryBarrier(GL_SHADER_STORAGE_BARRIER_BIT);
	glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 0, 0);
}

void ParticleSystem::Draw(ShaderProgram vertFragShader)
{
	vertFragShader.UseShader();

	glBindBuffer(GL_ARRAY_BUFFER, particleVAO);

	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(Particle), (void*)offsetof(Particle, position));
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(Particle), (void*)offsetof(Particle, velocity));
	glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, sizeof(Particle), (void*)offsetof(Particle, colour));
	glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE, sizeof(Particle), (void*)offsetof(Particle, alphaAge));
	glVertexAttribPointer(4, 4, GL_FLOAT, GL_FALSE, sizeof(Particle), (void*)offsetof(Particle, newVelocity));

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);
	glEnableVertexAttribArray(3);
	glEnableVertexAttribArray(4);

	glm::mat4 projection = glm::perspective(3.14159f / 4, 1280.0f / 720.0f, 0.1f, 100.0f);

	glm::mat4 view = glm::lookAt(glm::vec3(2, 2, 2), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));

	glm::mat4 model = glm::mat4(1.0f);

	vertFragShader.SetUniform("mvpMatrix", projection * view * model);

	vertFragShader.SetUniform("smoke", 0);
	vertFragShader.SetUniform("fire", 1);

	m_Tsmoke->Bind(0);
	m_Tfire->Bind(1);

	glDrawArrays(GL_POINTS, 0, MAX_PARTICLES);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
}
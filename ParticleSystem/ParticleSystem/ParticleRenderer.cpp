#include "ParticleRenderer.h"
#include "ShaderProgram.h"

#include "ext/matrix_transform.hpp"
#include "ext/matrix_clip_space.hpp"

#define NUM_PARTICLES 1024 * 1024
#define WORK_GROUP_SIZE 128

struct Particle {
	glm::vec4 position;
	glm::vec4 velocity;
	glm::vec4 colour;
};

ParticleRenderer::ParticleRenderer()
{
	glGenBuffers(1, &particleVAO);

	glBindBuffer(GL_SHADER_STORAGE_BUFFER, particleVAO);
	glBufferData(GL_SHADER_STORAGE_BUFFER, NUM_PARTICLES * sizeof(Particle), nullptr, GL_STATIC_DRAW);
	glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 0, particleVAO);
}

ParticleRenderer::~ParticleRenderer()
{
}

void ParticleRenderer::Update(ShaderProgram particleShader)
{
	glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 0, particleVAO);

	particleShader.UseShader();
	glDispatchCompute(NUM_PARTICLES / WORK_GROUP_SIZE, 1, 1);
	glMemoryBarrier(GL_SHADER_STORAGE_BARRIER_BIT);
}

void ParticleRenderer::Draw(ShaderProgram particleShader)
{
	particleShader.UseShader();

	glBindBuffer(GL_VERTEX_ARRAY, particleVAO);

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);

	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(Particle), 0);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(Particle), (void*)(4 * sizeof(float)));
	glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, sizeof(Particle), (void*)(8 * sizeof(float)));

	glDrawArrays(GL_POINTS, 0, NUM_PARTICLES);

	glBindBuffer(GL_VERTEX_ARRAY, 0);
}

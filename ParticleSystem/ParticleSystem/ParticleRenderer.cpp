#include "ParticleRenderer.h"
#include "ShaderProgram.h"

#include "ext/matrix_transform.hpp"
#include "ext/matrix_clip_space.hpp"

#define NUM_PARTICLES 1024 * 1024
#define WORK_GROUP_SIZE 128

struct Particle {
	glm::vec4 position{ 0, 0, 0, 0 };
	glm::vec4 velocity{ 0, 0, 0, 0 };
	glm::vec4 colour{ 0, 0, 0, 0 };
};

ParticleRenderer::ParticleRenderer()
{
	glGenBuffers(1, &particleVAO);

	glBindBuffer(GL_SHADER_STORAGE_BUFFER, particleVAO);
	glBufferData(GL_SHADER_STORAGE_BUFFER, NUM_PARTICLES * sizeof(Particle), nullptr, GL_STATIC_DRAW);
	glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 0, particleVAO);

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);
}

ParticleRenderer::~ParticleRenderer()
{
}

void ParticleRenderer::Draw(ShaderProgram particleShader)
{
}

void ParticleRenderer::Update()
{
}
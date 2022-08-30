#include "ParticleManager.h"

ParticleManager::ParticleManager()
{
	particle = new ParticleSystem;

	shader = new ShaderProgram("ParticleShader.vert", "ParticleShader.geom", "ParticleShader.frag");
}

ParticleManager::~ParticleManager()
{

}

void ParticleManager::SetPrem()
{
	premultiplied = new ShaderProgram("ParticlePremultiplied.comp");
}

void ParticleManager::UpdatePre()
{
	particle->Update(*premultiplied);
}

void ParticleManager::SetAdd()
{
	additive = new ShaderProgram("ParticleAdditive.comp");
}

void ParticleManager::UpdateAdd()
{
	particle->Update(*additive);
}

void ParticleManager::DrawParticle()
{
	particle->Draw(*shader);
}

void ParticleManager::SetTexture(std::string textureSetter)
{
}

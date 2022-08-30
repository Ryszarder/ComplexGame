#include "ParticleManager.h"

ParticleManager::ParticleManager()
{
	ParticleSystem newParticle;

}

ParticleManager::~ParticleManager()
{

}

void ParticleManager::UpdatePrem()
{
	ShaderProgram premultiplied("ParticlePremultiplied.comp");
}

void ParticleManager::UpdateAdd()
{
	ShaderProgram additive("ParticleAdditive.comp");
}

void ParticleManager::DrawParticle()
{
	ShaderProgram shader("ParticleShader.vert", "ParticleShader.geom", "ParticleShader.frag");

}

void ParticleManager::SetTexture(std::string textureSetter)
{
}

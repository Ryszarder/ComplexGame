#include "ParticleManager.h"
#include <iostream>

ParticleManager::ParticleManager()
{
	particle = new ParticleSystem;

	shader = new ShaderProgram("ParticleShader.vert", "ParticleShader.geom", "ParticleShader.frag");
}

ParticleManager::~ParticleManager()
{
	delete particle;
	delete shader;
	delete additive;
	delete premultiplied;
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

void ParticleManager::SetTexture()
{
	if (premultiplied != nullptr)
	{
		textureSet = "Texture/Smoke.png";
	}
	else if (additive != nullptr)
	{
		textureSet = "Texture/Fire.png";
	}
	particle->ParticleTexture(textureSet);
}
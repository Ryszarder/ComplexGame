#pragma once
#include "ParticleSystem.h"
#include "ShaderProgram.h"

class ParticleManager
{
public:

	ParticleManager();
	~ParticleManager();

	void SetPrem();

	void UpdatePre();

	void SetAdd();
	
	void UpdateAdd();

	void DrawParticle();

	void SetTexture(std::string textureSetter);

private:
	ParticleSystem* particle;

	ShaderProgram* shader;
	ShaderProgram* premultiplied;
	ShaderProgram* additive;
};


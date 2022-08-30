#pragma once
#include "ParticleSystem.h"
#include "ShaderProgram.h"

class ParticleManager
{
public:

	ParticleManager();
	~ParticleManager();

	void UpdatePrem();

	void UpdateAdd();

	void DrawParticle();

	void SetTexture(std::string textureSetter);

private:

};


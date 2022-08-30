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

	void SetTexture();

	//bool WindowScreen();

	void Run();

private:
	ParticleSystem* particle = nullptr;

	ShaderProgram* shader = nullptr;
	ShaderProgram* premultiplied = nullptr;
	ShaderProgram* additive = nullptr;

	//GLFWwindow* window = nullptr;

	std::string textureSet;
};


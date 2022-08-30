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
	if (premultiplied != nullptr)
	{
		UpdatePre();
	}
	else if (additive != nullptr)
	{
		UpdateAdd();
	}
	particle->Draw(*shader);
}

void ParticleManager::SetTexture()
{
	if (premultiplied != nullptr)
	{
		textureSet = "Texture/particle3.png";
	}
	else if (additive != nullptr)
	{
		textureSet = "Texture/Fire.png";
	}
	particle->ParticleTexture(textureSet);
}


/*
bool ParticleManager::WindowScreen()
{
	if (!glfwInit())
		return -1;
	
	window = glfwCreateWindow(1280, 720, "Particle", nullptr, nullptr);
	if (!window)
	{
		glfwTerminate();
		return -1;
	}
	
	glfwMakeContextCurrent(window);
	
	if (!gladLoadGL())
		return -1;
}
*/
void ParticleManager::Run()
{
	//while (!glfwWindowShouldClose(window))
	//{
	//	DrawParticle();
	//	
	//	
	//	
	//
	//	glfwSwapBuffers(window);
	//
	//	glfwPollEvents();
	//}
}


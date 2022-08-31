#include "ParticleManager.h"
#include <iostream>

int main(void)
{
	
	GLFWwindow* window;

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

	ParticleManager particleSmoke;
	particleSmoke.SetPrem();
	particleSmoke.SetTexture();

	ParticleManager particleFire;
	particleFire.SetAdd();
	particleFire.SetTexture();

	while (!glfwWindowShouldClose(window))
	{
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		particleSmoke.UpdatePre();
		particleSmoke.DrawParticle();

		particleFire.UpdateAdd();
		particleFire.DrawParticle();

		glfwSwapBuffers(window);

		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}
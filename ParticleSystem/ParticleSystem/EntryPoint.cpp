#include "Graphics.h"

#include <math.h>
#include "Utilities.h"
#include "ShaderProgram.h"
#include "ParticleSystem.h"
#include <iostream>

#include "glm.hpp"

#include "ext/matrix_transform.hpp"
#include "ext/matrix_clip_space.hpp"

int main(void)
{
	GLFWwindow* window;

	//Initialise GLFW, make sure it works. Put an error message here if you like

	if (!glfwInit())
		return -1;

	//Set resolution here, and give your window a different title
	window = glfwCreateWindow(1280, 720, "Particle", nullptr, nullptr);
	if (!window)
	{
		glfwTerminate();  //Again, you can put a real error message here
		return -1;
	}

	//This tells GLFW that the window we created is the one we should render to
	glfwMakeContextCurrent(window);

	//Tell GLAF to load all it's OpenGL functions
	if (!gladLoadGL())
		return -1;

	//glEnable(GL_BLEND);

	//glBlendFunc(GL_ONE, GL_ONE_MINUS_SRC_ALPHA);

	ParticleSystem particle;
	ParticleSystem particle2;

	ShaderProgram shader("ParticleShader.vert", "ParticleShader.geom", "ParticleShader.frag");
	ShaderProgram Premultiplied("ParticlePremultiplied.comp");
	ShaderProgram Additive("ParticleAdditive.comp");

	//The main 'game' loop
	while (!glfwWindowShouldClose(window))
	{
		//Clear the screen - eventually do rendering code here
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		particle.Update(Premultiplied);
		particle.Draw(shader); 

		particle2.Update(Additive);
		particle2.Draw(shader);

		//Swapping the buffers - this means this frame is over
		glfwSwapBuffers(window);

		//Tell GLFW to check if anything is going on with input, etc
		glfwPollEvents();
	}

	//If we get to this point, the window has close, so clean up GLFW and exit
	glfwTerminate();
	return 0;
}
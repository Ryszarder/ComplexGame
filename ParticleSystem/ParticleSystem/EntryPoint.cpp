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

	//glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);

	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);	//This one's for smoke (alpha)
	glBlendEquation(GL_FUNC_ADD);
	//glBlendFunc(GL_SRC_ALPHA, GL_ONE);
	glBlendFunc(GL_ONE, GL_ONE);	//This one's for fire (additive)





	glBlendFunc(GL_ONE, GL_ONE_MINUS_SRC_ALPHA);	//This is for premultiplied alpha - use it for everything!


	/*
	FragColour = colour;	//No premultiplied alpha

	if(isAlphaParticle)
	{
		FragColour = vec4(colour.rgb * colour.a, colour.a); //Premultiplied alpha
	}
	else
	{
		//It's an additive particle
		FragColour = vec4(colour.rgb, 0.0);
	}
	*/

	ParticleRenderer particle;

	ShaderProgram shader("ParticleShader.vert", "ParticleShader.geom", "ParticleShader.frag");
	ShaderProgram compute("ParticleShader.comp");

	//The main 'game' loop
	while (!glfwWindowShouldClose(window))
	{
		//Clear the screen - eventually do rendering code here
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		particle.Update(compute);

		particle.Draw(shader);

		//Swapping the buffers - this means this frame is over
		glfwSwapBuffers(window);

		//Tell GLFW to check if anything is going on with input, etc
		glfwPollEvents();
	}

	//If we get to this point, the window has close, so clean up GLFW and exit
	glfwTerminate();
	return 0;
}
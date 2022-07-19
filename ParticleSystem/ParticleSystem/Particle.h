#pragma once

#include "glm.hpp"

#include <vector>

struct Particle 
{
	glm::vec4 position;
	glm::vec4 velocity;
	glm::vec4 colour;
	glm::vec4 alphaAge;
	//float isAlpha; //Does this render alpha? If not it's additive.
	//float padding;
	//float padding2;
	//float padding3;
	//float age;
	//float padding4;
	//float padding5;
	//float padding6;
};
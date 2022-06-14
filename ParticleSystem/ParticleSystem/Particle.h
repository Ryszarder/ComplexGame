#pragma once

#include "glm.hpp"

#include <vector>

struct Particle 
{
	glm::vec4 position;
	glm::vec4 velocity;
	glm::vec4 colour;
	//bool isAlpha; //Does this render alpha? If not it's additive.
};
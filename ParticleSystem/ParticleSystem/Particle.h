#pragma once

#include "glm.hpp"

#include <vector>

struct Particle 
{
	glm::vec4 position;
	glm::vec4 velocity;
	glm::vec4 colour;
	glm::vec4 alphaAge;
	glm::vec4 newVelocity;
};
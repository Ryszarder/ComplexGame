#version 450

layout (location = 0) in vec4 Position;
layout (location = 1) in vec4 Velocity;
layout (location = 2) in vec4 Colour;

out vec4 _colour;

uniform mat4 mvpMatrix;

void main()
{
	_colour = Colour;
	gl_Position = mvpMatrix * Position;
}
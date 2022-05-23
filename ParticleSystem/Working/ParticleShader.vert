#version 450

layout (location = 0) in vec3 Position;
layout (location = 0) in vec3 Velocity;
layout (location = 0) in vec3 Colour;

out vec3 _colour;

void main()
{
	gl_Position = vec4(Position, 1.0);
}
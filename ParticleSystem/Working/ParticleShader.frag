#version 450

out vec4 FragColour;

in vec4 _colour

void main()
{
	FragColour = _colour;
}
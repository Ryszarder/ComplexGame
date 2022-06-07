#version 450

out vec4 FragColour;

in vec2 UVs;
in vec4 Colour;

uniform sampler2D sprite;

void main()
{
	vec4 texColour = texture(sprite, UVs);
	if(texColour.a < 0.1f)
		discard;
	FragColour = texColour * Colour;
}
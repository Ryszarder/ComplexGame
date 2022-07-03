#version 450

out vec4 FragColour;

in vec2 UVs;
in vec4 Colour;
//in float Alpha;

uniform sampler2D sprite;

void main()
{
	vec4 texColour = texture(sprite, UVs);
	
	vec4 ParticleTex = texColour * Colour;
	
	//if(Alpha == 1.0f)
	//{
	//	FragColour = vec4(ParticleTex.rgb * ParticleTex.a, ParticleTex.a);
	//}
	//else
	//{
		FragColour = vec4(ParticleTex.rgb, 0.0);
	//}
}
#version 450

out vec4 FragColour;

in vec2 UVs;
in vec4 Colour;
in float Alpha;

uniform sampler2D partTex;

void main()
{	
	if(Alpha > 0.5f)
	{
		vec4 texColour = texture(partTex, UVs);
		vec4 ParticleTex = texColour * Colour;
		
		FragColour = vec4(ParticleTex.rgb * ParticleTex.a, ParticleTex.a);
	}
	else
	{
		vec4 texColour = texture(partTex, UVs);
		vec4 ParticleTex = texColour * Colour;
		
		FragColour = vec4(ParticleTex.rgb, 0.0);
	}
}
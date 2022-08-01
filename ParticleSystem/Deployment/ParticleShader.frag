#version 450

out vec4 FragColour;

in vec2 UVs;
in vec4 Colour;
in float Alpha;

uniform sampler2D smoke;
uniform sampler2D fire;

void main()
{	
	if(Alpha > 0.5f)
	{
		vec4 texColour = texture(smoke, UVs);
		vec4 ParticleTex = texColour * Colour;
		
		FragColour = vec4(ParticleTex.rgb * ParticleTex.a, ParticleTex.a);
	}
	else
	{
		vec4 texColour = texture(fire, UVs);
		vec4 ParticleTex = texColour * Colour;
		
		FragColour = vec4(ParticleTex.rgb, 0.0);
	}
}
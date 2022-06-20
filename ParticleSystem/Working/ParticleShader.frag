#version 450

out vec4 FragColour;

in vec2 UVs;
in vec4 Colour;
in float Alpha;

uniform sampler2D sprite;

void main()
{
	vec4 texColour = texture(sprite, UVs);
	//if(texColour.a < 0.1f)
		//discard;
	FragColour = texColour * Colour;
	
	if(Alpha == 1.0f)
	{
		FragColour = vec4(Colour.rgb * Colour.a, Colour.a);
	}
	else
	{
		FragColour = vec4(Colour.rgb, 0.0);
	}
}
#version 450

out vec4 FragColour;

in vec2 UVs;
in vec4 Colour;
//in float Alpha;

uniform sampler2D sprite;

void main()
{
	vec4 texColour = texture(sprite, UVs);
	//if(texColour.a < 0.1f)
		//discard;
	
	//FragColour = texColour * Colour;
	vec4 test = texColour * Colour;

	//FragColour = vec4(test.rgb * test.a, test.a);
	
	FragColour = vec4(test.rgb, 0.0);
	
	//if(Alpha == 1.0f)
	//{
	//	FragColour = vec4(Colour.rgb * Colour.a, Colour.a);
	//}
	//else
	//{
	//	FragColour = vec4(Colour.rgb, 0.0);
	//}
}
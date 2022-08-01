#version 450

layout (points) in;
layout (triangle_strip, max_vertices = 4) out;

out vec2 UVs;
out vec4 Colour;
out float Alpha;

in vec4 vertColour[];
in float vertAlpha[];

void main()
{
	float inverseAspect = 720.0f / 1280.0f;
	
	gl_Position = gl_in[0].gl_Position - vec4(0.1f * inverseAspect, -0.1f, 0, 0);
	UVs = vec2(1.0, 0.0);
	Colour = vertColour[0];
	Alpha = vertAlpha[0];
	EmitVertex();
	
	gl_Position = gl_in[0].gl_Position - vec4(-0.1f * inverseAspect, -0.1f, 0, 0);
	UVs = vec2(0.0, 0.0);		
	Colour = vertColour[0];
	Alpha = vertAlpha[0];
	EmitVertex();
	
	gl_Position = gl_in[0].gl_Position - vec4(0.1f * inverseAspect, 0.1f, 0, 0);
	UVs = vec2(1.0, 1.0);
	Colour = vertColour[0];
	Alpha = vertAlpha[0];
	EmitVertex();
	
	gl_Position = gl_in[0].gl_Position - vec4(-0.1f * inverseAspect, 0.1f, 0, 0);
	UVs = vec2(0.0, 1.0);
	Colour = vertColour[0];
	Alpha = vertAlpha[0];
	EmitVertex();
	
	EndPrimitive();
}
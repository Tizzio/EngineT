#version 330

//layout (location = 0) out vec3 Color;
layout (location = 0) in vec3 Position;
layout (location = 1) in vec2 TexCoord;
layout (location = 2) in vec3 Normal; 

uniform mat4 gWVP;
uniform mat4 gWorld;

out vec2 TexCoord0;
out vec3 Normal0;
out vec3 WorldPos0;
out vec4 randColor;

float rand(vec2 co){
    return fract(sin(dot(co.xy ,vec2(12.9898,78.233))) * 43758.5453);
}

void main()
{
	gl_Position = gWVP * vec4(Position, 1.0);
	TexCoord0 = TexCoord;
	randColor = vec4(Position, 1.0f);
	Normal0 = (gWorld * vec4(Normal, 0.0)).xyz;
	WorldPos0 = (gWorld * vec4(Position, 1.0)).xyz;
}
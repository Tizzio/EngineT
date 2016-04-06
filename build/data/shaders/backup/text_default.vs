#version 330

layout (location = 0) in vec2 Position;
layout (location = 1) in vec2 TexCoord;
layout (location = 2) in vec4 Color;

uniform mat4 gWVP;

out vec2 TexCoord0;
out vec4 Color0;

void main()
{
	gl_Position = gWVP * vec4(Position.x, Position.y, 1.0, 1.0);
	TexCoord0 = TexCoord;
	Color0 = Color;
}
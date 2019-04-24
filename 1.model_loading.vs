#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 2) in vec2 aTexCoords;

uniform mat4 M;
uniform mat4 V;
uniform mat4 P;

out vec2 TexCoords;

void main()
{	
	TexCoords = aTexCoords;
	gl_Position = P * V * M * vec4(aPos, 1.0);	
}
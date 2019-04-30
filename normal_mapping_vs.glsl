#version 330 core

layout (location = 0) in vec3 position;
layout (location = 2) in vec2 texCoords;

uniform mat4 M;
uniform mat4 V;
uniform mat4 P;
uniform vec3 lightPos;
uniform vec3 viewPos;

out vec4 gl_Position;
out vec2 TexCoords;

void main()
{	
	TexCoords = texCoords;
	gl_Position = P*V*M * vec4(position, 1.0);	
}
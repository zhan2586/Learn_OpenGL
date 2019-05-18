#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexCoords;
layout (location = 2) in vec3 aNormal;

uniform mat4 M;
uniform mat4 V;
uniform mat4 P;

out vec2 TexCoords;
out vec3 worldPos;
out vec3 Normal;

void main()
{	
	TexCoords = aTexCoords;
	worldPos = vec3(M * vec4(aPos, 1.0));
	Normal = mat3(M) * aNormal;

	gl_Position = P * V * vec4(worldPos, 1.0);	
}
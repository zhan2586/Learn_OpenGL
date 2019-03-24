#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoords;

uniform mat4 M;
uniform mat4 V;
uniform mat4 P;
uniform vec3 lightPos;
uniform vec3 viewPos;

out vec2 TexCoords;
out vec3 fragPos;
out vec3 Normal;

void main()
{	
	TexCoords = aTexCoords;
	fragPos = vec3(M * vec4(aPos, 1.0));
	Normal = mat3(transpose(inverse(M))) * aNormal;

	gl_Position = P*V*M * vec4(aPos, 1.0);	
}
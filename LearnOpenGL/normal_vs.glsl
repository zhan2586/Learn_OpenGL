#version 330 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec2 texCoords;
layout (location = 3) in vec3 tangent;
layout (location = 4) in vec3 bitangent;

uniform mat4 M;
uniform mat4 V;
uniform mat4 P;
uniform vec3 lightPos;
uniform vec3 viewPos;

out vec2 TexCoords;
out vec3 fragPos;
out vec3 TangentFragPos;
out vec3 TangentLightPos;
out vec3 TangentViewPos;

void main()
{	
	TexCoords = texCoords;
	fragPos = vec3(M * vec4(position, 1.0));

	mat3 normalMatrix = transpose(inverse(mat3(M)));
    vec3 T = normalize(normalMatrix * tangent);
    vec3 B = normalize(normalMatrix * bitangent);
    vec3 N = normalize(normalMatrix * normal);  

	mat3 TBN = transpose(mat3(T, B, N));  
    TangentLightPos = TBN * lightPos;
    TangentViewPos  = TBN * viewPos;
    TangentFragPos  = TBN * fragPos;
	
	gl_Position = P * V * M * vec4(position, 1.0);	
}
#version 330 core

uniform sampler2D diffuseMap;
uniform sampler2D normalMap;

in vec2 TexCoords;

out vec4 fragColor;

void main()
{
	fragColor = texture(diffuseMap, TexCoords);
	
}
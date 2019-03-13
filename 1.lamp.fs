#version 330 core

in vec3 fragPos;

uniform vec3 objectColor;
uniform vec3 lightColor;

out vec4 fragColor;

void main()
{	
	fragColor = vec4(1.0);
}
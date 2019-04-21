#version 330 core

in vec3 TexCoords;
uniform samplerCube skybox;
out vec4 fragColor;

const float offset = 1.0 / 300.0;

void main()
{
	
	fragColor = vec4(col, 1.0);
}
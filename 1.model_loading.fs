#version 330 core

uniform sampler2D texture_diffuse1;
uniform vec3 cameraPos;

in vec2 TexCoords;

out vec4 fragColor;

void main()
{
	fragColor = texture(texture_diffuse1, TexCoords);
}
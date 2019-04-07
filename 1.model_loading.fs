#version 330 core

uniform vec3 objectColor;
uniform vec3 lightColor;
uniform vec3 lightPos;
uniform vec3 viewPos;


struct Material{
	// vec3 ambient;
	sampler2D diffuse;
	sampler2D specular;
	float shininess;
};

struct Light{
	vec3 position;

	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};

uniform Material material;
uniform Light light;

uniform sampler2D objTexture;

in vec2 TexCoords;
in vec3 Normal;
in vec3 fragPos;

out vec4 fragColor;

void main()
{		
	fragColor = texture(objTexture, TexCoords);
}
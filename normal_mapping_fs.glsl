#version 330 core

uniform sampler2D diffuseMap;
uniform sampler2D normalMap;
uniform vec3 lightPos;
uniform vec3 viewPos;

in vec2 TexCoords;
in vec3 fragPos;

out vec4 fragColor;

void main()
{
	vec3 normalMapSampler = texture(normalMap, TexCoords).rgb;
	vec3 normal = normalize(normalMapSampler * 2.0 - 1.0);
	vec3 color = texture(diffuseMap, TexCoords).rgb;
	
	vec3 ambient = 0.1 * color;

	vec3 lightDir =  lightPos - fragPos;
	float diff = max(dot(lightDir, normal), 0.0);
	vec3 diffuse = diff * color;

	vec3 viewDir = viewPos - fragPos;
	vec3 halfWayDir = normalize(lightDir + viewDir);

	float spec = pow(max(dot(normal, halfWayDir), 0.0), 4.0);
	vec3 specular = vec3(.02) * spec;
	fragColor = vec4(ambient + diffuse + specular, 1.0);
	
}
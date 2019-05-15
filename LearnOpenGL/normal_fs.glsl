#version 330 core

uniform sampler2D diffuseMap;
uniform sampler2D normalMap;
uniform vec3 cameraPos;

in vec2 TexCoords;
in vec3 fragPos;
in vec3 TangentFragPos;
in vec3 TangentLightPos;
in vec3 TangentViewPos;

out vec4 fragColor;

void main()
{
	vec3 normal = texture(normalMap, TexCoords).rgb;
	normal = normalize(normal * 2.0 - 1.0);

	vec3 color = texture(diffuseMap, TexCoords).rgb;
	vec3 ambient = 0.2 * color;

	vec3 lightDir = normalize(TangentLightPos - TangentFragPos);
	float diff = dot(lightDir, normal);
	vec3 diffuse = diff * color;

	vec3 viewDir = normalize(TangentViewPos - TangentFragPos);
	vec3 reflDir = reflect(-lightDir, normal);
	vec3 halfwayDir = normalize(lightDir + viewDir);
	float spec = pow(dot(normal, halfwayDir), 32.0);
	vec3 specular = vec3(0.3) * spec;

	fragColor = vec4(ambient + diffuse + specular, 1.0);
	// fragColor = vec4(TexCoords.xy, 0.2, 1.0);
}
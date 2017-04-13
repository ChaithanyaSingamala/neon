#version 140

out vec4 fragColor;

in vec3 posInWorld;
in vec3 normalInWorld;

uniform vec3 objectColor;
uniform vec3 lightColor;

uniform vec3 lightPos;

void main()
{
	vec3 normal = normalize(normalInWorld);
	vec3 lightDir = normalize(lightPos - posInWorld);
	float diffuseFactor = max(dot(normal,lightDir), 0.0);

	fragColor = vec4(lightColor * objectColor * diffuseFactor, 1.0);
}
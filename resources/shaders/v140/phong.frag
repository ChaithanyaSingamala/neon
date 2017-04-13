#version 140

out vec4 fragColor;

in vec3 posInWorld;
in vec3 normalInWorld;

uniform vec3 objectColor;
uniform vec3 lightColor;

uniform vec3 lightPos;
uniform vec3 viewPos;

void main()
{
	vec3 diffuseColor = vec3(0.0);
	vec3 normal = normalize(normalInWorld);
	vec3 lightDir = normalize(lightPos - posInWorld);
	float diffuseFactor = max(dot(normal,lightDir), 0.0);
	//diffuseColor = diffuseFactor * lightColor;

	float specularStrength = 0.5;
	float shininess = 32.0;
	vec3 viewDir = normalize(viewPos - posInWorld);
	vec3 reflectDir = reflect(lightDir, normal);
	float specFactor = pow(max(dot(viewDir,reflectDir), 0.0), shininess);
	
	fragColor = vec4(objectColor * (specFactor + diffuseFactor) * lightColor, 1.0);
}
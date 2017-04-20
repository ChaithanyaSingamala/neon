#version 300 es
precision mediump float;

in vec3 vertexPosition;
in vec2 vertexUV;
in vec3 vertexNormal;

uniform mat4 model;
uniform mat4 view;
uniform mat4 proj;
uniform mat3 normalMatrix;

out vec3 vColor;
out vec2 vUV;

out vec3 posInWorld;
out vec3 normalInWorld;

void main()
{
	gl_Position = proj * view * model * vec4(vertexPosition, 1.0);
	vUV = vertexUV;
	posInWorld = vec3(model * vec4(vertexPosition, 1.0));
	
	// assuming The normal matrix is defined as the transpose of the inverse of the upper-left corner of the model matrix
	//mat3 normalMatrix = mat3(transpose(inverse(model)));
	normalInWorld = normalMatrix * vertexNormal;
}
#version 140

in vec3 vertexPosition;
in vec2 vertexUV;
in vec3 vertexColor;

uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projMatrix;

out vec3 vColor;
out vec2 vUV;

void main()
{
	gl_Position = projMatrix * viewMatrix * modelMatrix * vec4(vertexPosition, 1.0);
	vColor = vertexColor;
	vUV = vertexUV;
}
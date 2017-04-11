#version 140

in vec3 vertexPosition;
in vec2 vertexUV;
in vec3 vertexColor;

out vec3 vColor;
out vec2 vUV;

void main()
{
	gl_Position = vec4(vertexPosition, 1.0);
	vColor = vertexColor;
	vUV = vertexUV;
}
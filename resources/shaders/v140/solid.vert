#version 140

in vec3 vertexPosition;

uniform mat4 model;
uniform mat4 view;
uniform mat4 proj;


void main()
{
	gl_Position = proj * view * model * vec4(vertexPosition, 1.0);
}
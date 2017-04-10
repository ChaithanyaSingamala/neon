#version 430

in layout(location=0) vec3 position;
in layout(location=1) vec3 inColor;

out vec3 vColor;

void main()
{
	gl_Position = vec4(position, 1.0);
	vColor = inColor;
}